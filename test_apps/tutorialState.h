#ifndef TUTORIAL_STATE_H
#define TUTORIAL_STATE_H

#include "tutorial.h"

#include <warped/state.h>

class TutorialState : public State {
public:
  TutorialState();
  
  unsigned int getStateSize() const;
  void copyState( const State* state );
};

#endif