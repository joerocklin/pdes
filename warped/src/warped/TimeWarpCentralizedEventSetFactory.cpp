// See copyright notice in file Copyright in the root directory of this archive.

#include "TimeWarpEventSet.h"
#include "TimeWarpCentralizedEventSetFactory.h"
#include "TimeWarpCentralizedEventSet.h"
#include "TimeWarpSenderQueue.h"
#include "SimulationConfiguration.h"
using std::cerr;
using std::endl;
using namespace warped;

TimeWarpCentralizedEventSetFactory::TimeWarpCentralizedEventSetFactory(){}

TimeWarpCentralizedEventSetFactory::~TimeWarpCentralizedEventSetFactory(){
  // myEventSet will be deleted by the end user - the
  // TimeWarpSimulationManager.
}

Configurable *
TimeWarpCentralizedEventSetFactory::allocate( SimulationConfiguration &,
					      Configurable * ) const {
  
  TimeWarpCentralizedEventSet *retval = 0;
  cerr << "Unknown EVENTLIST choice encountered" << endl;
  cerr << "Exiting simulation ... " << endl;
  exit(-1);

  return retval;
}

