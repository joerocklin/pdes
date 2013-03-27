// See copyright notice in file Copyright in the root directory of this archive.

#include "DefaultCommunicationManager.h"

using namespace warped;

DefaultCommunicationManager::DefaultCommunicationManager( PhysicalCommunicationLayer *initPhysicalLayer, 
							  TimeWarpSimulationManager *initSimulationManager) :
  CommunicationManagerImplementationBase( initPhysicalLayer, initSimulationManager ){};

DefaultCommunicationManager::~DefaultCommunicationManager(){};

 
