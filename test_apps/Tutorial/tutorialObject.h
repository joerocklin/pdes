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
using namespace warped;

class TutorialObject : public SimulationObject {
public:
  TutorialObject( const int initObjectId );
  
  State* allocateState();
  void deallocateState( const State* state );
  void reclaimEvent( const Event* event );
  
  void initialize();
  void executeProcess();
  void finalize();
  
  const string &getName() const { return this->name; }
  const int getId() const { return this->id; }
  const unsigned int getLoopCount() const { return this->loop_count; }

  void setSendAck(bool ack) { this->sendAck = ack; }
  void setLoopCount(unsigned int count) { this->loop_count = count; }

private:
  /// The ID of this simulation object.
  int id;
  string name;
  
  unsigned int loop_count;
  
  bool sendAck;
  
};

#endif