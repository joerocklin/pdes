#include "tutorialState.h"

#include <warped/warped.h> // for ASSERT

TutorialState::TutorialState() {
  enter_method;
}

unsigned int TutorialState::getStateSize() const {
  enter_method;
  return sizeof(TutorialState);
}

void TutorialState::copyState(const State* state) {
  enter_method;
  
  ASSERT( state != 0 );
  const TutorialState *myState = dynamic_cast<const TutorialState *>(state);
}