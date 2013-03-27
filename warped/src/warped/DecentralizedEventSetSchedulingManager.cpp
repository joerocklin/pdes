// See copyright notice in file Copyright in the root directory of this archive.

#include "DecentralizedEventSetSchedulingManager.h"
#include "TimeWarpDecentralizedEventSetFactory.h"

using namespace warped;

DecentralizedEventSetSchedulingManager::DecentralizedEventSetSchedulingManager( TimeWarpSimulationManager* simMgr) : 
  mySimulationManager(simMgr), 
  myEventSet( 0 ), 
  simulationObjectsArray( 0 ) {}

DecentralizedEventSetSchedulingManager::~DecentralizedEventSetSchedulingManager() {
  delete simulationObjectsArray;
}

void
DecentralizedEventSetSchedulingManager::initialize(TimeWarpEventSet *eventSet,
                                                   vector<SimulationObject*> *simObjArray){
  myEventSet = eventSet;
  ASSERT( myEventSet != 0 );
  // ownership of scheduler's list is transferred here.
  // the scheduler is now responsible for deleting this memory
  simulationObjectsArray = simObjArray;
}

