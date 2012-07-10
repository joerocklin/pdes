#include "simternetApplication.h"

#include <warped/RoundRobinPartitioner.h>

#include <vector>

SimternetApplication::SimternetApplication() {

}

/** registerDeserializers
 * This is called after class creation.
 */
void SimternetApplication::registerDeserializers() {

}

/** initialize
 * This is called after the deserializers are registered.
 * Common actions performed here include:
 *  - parsing configuration files
 */
int SimternetApplication::initialize( vector<string> &arguments ) {
  
  return 0;
}

/** getNumberOfSimulationObjects
 * Called after initialize. 
 */
int SimternetApplication::getNumberOfSimulationObjects( int mgrId ) const {

  return this->numObjects;
}


string SimternetApplication::getCommandLineParameters() const {
    
  return "foo";
}

/** getPartitionInfo
 * After Warped has initialized the simulation, this method is called. This 
 * partitions the simulation objects based on the number of processors available.
 * 
 * NOTE - Other examples use this call to create the objects via a call to
 *        getSimulationObjects
 */
const PartitionInfo* SimternetApplication::getPartitionInfo( unsigned int numProcessorsAvailable ) {
  const PartitionInfo *ret_partition = 0;
  
  // Select a partitioning algorithm
  Partitioner *myPartitioner = new RoundRobinPartitioner();
  
  // Create some simulation objects and partition them  
  vector<SimulationObject *> *objects = getSimulationObjects();
  ret_partition = myPartitioner->partition( objects, numProcessorsAvailable );
  delete objects;
  
  // WARNING: Returning NULL here will cause a segfault
  return ret_partition;
}

/** getSmulationObjects
 * Create the initial set of simulation objects
 */
vector<SimulationObject *> *SimternetApplication::getSimulationObjects() {
  vector<SimulationObject *> *simObjects = new vector<SimulationObject *>;
  
  for (int i = 0; i < numObjects; i++) {
//    simObjects->push_back( new TutorialObject(i) );
  }
  
  return simObjects;
}


int SimternetApplication::finalize() {
  
  return 0;
}
