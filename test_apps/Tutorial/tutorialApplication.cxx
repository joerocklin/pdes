#include "tutorial.h"
#include "tutorialApplication.h"
#include "tutorialObject.h"

#include <warped/RoundRobinPartitioner.h>
#include <utils/ArgumentParser.h>

#include <vector>

TutorialApplication::TutorialApplication() {
  enter_method;
  this->numObjects = 5;
  this->loop_count = 1;
}

/** registerDeserializers
 * This is called after class creation.
 */
void TutorialApplication::registerDeserializers() {
  enter_method;
}

/** initialize
 * This is called after the deserializers are registered.
 * Common actions performed here include:
 *  - parsing configuration files
 */
int TutorialApplication::initialize( vector<string> &arguments ) {
  enter_method;
  
  this->getArgumentParser().checkArgs( arguments );
  
  return 0;
}

ArgumentParser &TutorialApplication::getArgumentParser() {
  static ArgumentParser::ArgRecord args[] = {
    { "-nodes", "Number of nodes to use (default 5)", &numObjects, ArgumentParser::INTEGER, false },
    { "-loops", "Number of times to loop the nodes (default 1)", &loop_count, ArgumentParser::INTEGER, false},
    { "-ack", "Send acknowledge messages", &sendAcks, ArgumentParser::BOOLEAN, false },
    { "-debug", "Debug level", &::debug_level, ArgumentParser::INTEGER, false },
    { "", "", 0 }
  };
  static ArgumentParser *myArgParser = new ArgumentParser( args );
  return *myArgParser;
}

/** getNumberOfSimulationObjects
 * Called after initialize. 
 */
int TutorialApplication::getNumberOfSimulationObjects( int mgrId ) const {
  enter_method;

  return this->numObjects;
}


string TutorialApplication::getCommandLineParameters() const {
  enter_method;
  
  return "foo";
}

/** getPartitionInfo
 * After Warped has initialized the simulation, this method is called. This 
 * partitions the simulation objects based on the number of processors available.
 * 
 * NOTE - Other examples use this call to create the objects via a call to
 *        getSimulationObjects
 */
const PartitionInfo* TutorialApplication::getPartitionInfo( unsigned int numProcessorsAvailable ) {
  enter_method;
  
  if (debug_level > 2) { cout << "--- numProcessorsAvailable: " << numProcessorsAvailable << endl; }
  const PartitionInfo *ret_partition = 0;
  
  // Select a partitioning algorithm
  Partitioner *myPartitioner = new RoundRobinPartitioner();
  
  // Create some simulation objects and partition them  
  vector<SimulationObject *> *objects = getSimulationObjects();
  ret_partition = myPartitioner->partition( objects, numProcessorsAvailable );
  delete objects;  // 
  
  // WARNING: Returning NULL here will cause a segfault
  return ret_partition;
}

/** getSmulationObjects
 * Create the initial set of simulation objects
 */
vector<SimulationObject *> *TutorialApplication::getSimulationObjects() {
  enter_method;
  
  TutorialObject *obj = NULL;
  vector<SimulationObject *> *simObjects = new vector<SimulationObject *>;
  
  for (int i = 0; i < numObjects; i++) {
    obj = new TutorialObject(i);
    obj->setSendAck(this->sendAcks);
    obj->setLoopCount(this->loop_count);
    simObjects->push_back( obj );
  }
  
  return simObjects;
}

int TutorialApplication::finalize() {
  enter_method;
  
  return 0;
}
