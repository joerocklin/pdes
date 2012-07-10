#include "tutorial.h"
#include "tutorialObject.h"
#include "tutorialState.h"
#include "tutorialMessage.h"

#include <warped/SimulationManager.h>
#include <warped/IntVTime.h>

#include <sstream>
using namespace std;

TutorialObject::TutorialObject( const int initid ) {
  print_method_string;
  ostringstream tmpname;
  
  this->id = initid;
  cout << ": " << this->id << endl;
  
  tmpname << "ID_" << initid;
  this->name = tmpname.str();
}

State* TutorialObject::allocateState() {
  method_with_id(this->id);
  return new TutorialState();
}

void TutorialObject::deallocateState( const State* state ) {
  method_with_id(this->id);
  
  delete state;
}

void TutorialObject::reclaimEvent( const Event* event ) {
  method_with_id(this->id);
  
  delete event;
}

/** initialize
 * To kick off the simulation process, we need to create simulation events.
 * In this tutorial, we send a message around the 'ring' of simulation objects,
 * so the only object which needs an initial message will be the first object.
 * As an initialization process we will have the first object send a message to
 * itself.
 */
void TutorialObject::initialize() {
  method_with_id(this->id);
  
  if (this->id == 0) {
    // Get the time execution is starting
    IntVTime sendTime = dynamic_cast<const IntVTime&> (getSimulationTime());
  
    TutorialMessage* newMessage = new TutorialMessage(sendTime, sendTime + 1, this, this);
    newMessage->setSourceObject(getName());
    newMessage->setSinkObject("");
  
    this->receiveEvent(newMessage);
  }
}

void TutorialObject::executeProcess() {
  method_with_id(this->id);
  TutorialMessage* recvMsg;
  TutorialMessage* newMsg;
  SimulationObject *msgRecvObject = NULL;
  ostringstream recvname;
  
  // Get the time execution is starting
  IntVTime startTime = dynamic_cast<const IntVTime&> (getSimulationTime());
  
  // Init some other times we will use
  IntVTime sendTime = startTime;
  IntVTime recvTime = startTime;
  
  // Get our current state
  TutorialState *myState = (TutorialState *) getState();
  
  // Process any incoming events
	while (true == haveMoreEvents()) {
    recvMsg = (TutorialMessage*) getEvent();
    
    if (recvMsg != NULL) {
      SimulationObject *msgSourceObject = getObjectHandle(recvMsg->getSourceObject());
      
      cout << "--- " << this->id << " received event from " 
        << msgSourceObject->getName() << " at t" << startTime << endl;
      
      // If we are the first object and we receive a message from someone other
      // than ourselves, the the simulation has finished
      if (this->getId() == 0 && msgSourceObject->getName() != "ID_0") {
        break;
      }
      
      // Determine the receiver
      recvname << "ID_" << this->getId() + 1;
      msgRecvObject = getObjectHandle(recvname.str());
      if (msgRecvObject == NULL) {
        msgRecvObject = getObjectHandle("ID_0");
      }
      
      // Set the send & receive times for the new message
      sendTime = startTime + 1;
      recvTime = startTime + 2;         
      
      // Create the new message
      newMsg = new TutorialMessage(sendTime, recvTime, this, msgRecvObject);
      newMsg->setSourceObject(getName());
      newMsg->setSinkObject(msgRecvObject->getName());
      
      cout << "--- " << this->id << " sending message to "
        << msgRecvObject->getName() << " at t" << sendTime 
        << " to receive at t" << recvTime << endl;
        
      msgRecvObject->receiveEvent(newMsg);
    }
  }
  
  cout << "--- " << this->id << " finished processing events" << endl;
}

void TutorialObject::finalize() {
  method_with_id(this->id);
}
