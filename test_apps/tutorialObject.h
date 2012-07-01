#ifndef TUTORIAL_OBJECT_H
#define TUTORIAL_OBJECT_H

#include "tutorial.h"
#include "tutorialState.h"

#include <warped/warped.h>
#include <warped/SimulationObject.h>
#include <warped/State.h>
#include <warped/Event.h>

#include <iostream>
using namespace std;

class TutorialObject : public SimulationObject {
public:
  TutorialObject( const int initObjectId );
  
  State* allocateState();
  void deallocateState( const State* state );
  void reclaimEvent( const Event* event );
  
  void initialize();
  void executeProcess();
  void finalize();
  
  const string &getName() const { enter_method; return objectName; }

private:
  /// The name of this simulation object.
  string objectName;
  
};

#endif