// See copyright notice in file Copyright in the root directory of this archive.

#include "AggressiveOutputManager.h"
#include "TimeWarpSimulationManager.h"
#include "Event.h"

using namespace warped;

AggressiveOutputManager::AggressiveOutputManager( TimeWarpSimulationManager *simMgr ) :
  OutputManagerImplementationBase( simMgr ){
}

AggressiveOutputManager::~AggressiveOutputManager(){}

void
AggressiveOutputManager::rollback( SimulationObject *object,
				   const VTime &rollbackTime ){
  OutputEvents &outputEvents = getOutputEventsFor( *(object->getObjectID()) );
  vector<const Event *> *eventsToCancel = outputEvents.getEventsSentAtOrAfterAndRemove( rollbackTime );
  
  if( eventsToCancel->size() > 0 ){
    getSimulationManager()->cancelEvents( *eventsToCancel );
  }

  delete eventsToCancel;
}
