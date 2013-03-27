// See copyright notice in file Copyright in the root directory of this archive.

#include "SequentialConfigurationManager.h"

using namespace warped;

SequentialConfigurationManager::SequentialConfigurationManager( Application *initApplication )
  : mySimulationManager( new SequentialSimulationManager( initApplication ) ),
    myEventSetFactory(new EventSetFactory()){}

SequentialConfigurationManager::~SequentialConfigurationManager(){
  delete myEventSetFactory;
  delete mySimulationManager;
}

void
SequentialConfigurationManager::configure( SimulationConfiguration &configuration ){
  mySimulationManager->configure( configuration );
}

SimulationManager *
SequentialConfigurationManager::getSimulationManager(){
  return mySimulationManager;
}
