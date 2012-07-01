#include "tutorial.h"
#include "tutorialObject.h"
#include "tutorialState.h"

#include <warped/SimulationManager.h>

#include <sstream>
using namespace std;

TutorialObject::TutorialObject( const int initObjectId ) {
  enter_method;
  ostringstream tmpname;
  
  tmpname << "ID" << initObjectId;
  
  this->objectName = tmpname.str();
}

State* TutorialObject::allocateState() {
  enter_method;
  return new TutorialState();
}

void TutorialObject::deallocateState( const State* state ) {
  enter_method;
  
  delete state;
}

void TutorialObject::reclaimEvent( const Event* event ) {
  enter_method;
  
  delete event;
}

void TutorialObject::initialize() {
  enter_method;
}

void TutorialObject::executeProcess() {
  enter_method;
}

void TutorialObject::finalize() {
  enter_method;
}