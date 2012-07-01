#include "tutorial.h"
#include "tutorialApplication.h"
#include "tutorialObject.h"

#include <warped/RoundRobinPartitioner.h>

#include <vector>

TutorialApplication::TutorialApplication() {
  enter_method;
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
  
  return 0;
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
  cout << "--- numProcessorsAvailable: " << numProcessorsAvailable << endl;
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
  
  vector<SimulationObject *> *simObjects = new vector<SimulationObject *>;
  
  for (int i = 0; i < numObjects; i++) {
    simObjects->push_back( new TutorialObject(i) );
  }
  
  return simObjects;
}



int TutorialApplication::finalize() {
  enter_method;
  
  return 0;
}
