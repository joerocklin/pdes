#include "tutorial.h"
#include "tutorialMessage.h"

#include <warped/IntVTime.h>
#include <warped/ObjectID.h>

using namespace warped;

// The constructor for DefaultEvent needs to be called as well
TutorialMessage::TutorialMessage(
                const VTime &sendTime,
                const VTime &recvTime,
                SimulationObject *sender,
                SimulationObject *receiver)
  : DefaultEvent(sendTime ,recvTime, sender, receiver) {
  enter_method;
  this->flags = 0;
}

// Constructor called by deserializer.
TutorialMessage::TutorialMessage(const VTime &sendTime,
                const VTime &recvTime,
                const ObjectID &sender,
                const ObjectID &receiver,
                unsigned int initEventId)
  :DefaultEvent(sendTime ,recvTime, sender, receiver, initEventId) {
  enter_method; 
  this->flags = 0;
}

const string &TutorialMessage::getDataType() const {
  enter_method;
  return this->getTutorialMessageDataType();
}

const string &TutorialMessage::getTutorialMessageDataType() {
  enter_method;
  static string TutorialMessageDataType = "TutorialMessage";
  return TutorialMessageDataType;
}

bool TutorialMessage::eventCompare(const Event* event) {
  enter_method;
  
  // Cast the parameter event to our type
  TutorialMessage *tutorialEvent = (TutorialMessage*) event;
  return (
    // Include this call to compare base-class parameters
    compareEvents(this, event) &&
    
    // Include any comparisons specific to TutorialMessage members
    this->sinkObject == tutorialEvent->sinkObject &&
    this->sourceObject == tutorialEvent->sourceObject &&
    this->flags == tutorialEvent->flags
  );
}

void TutorialMessage::serialize(SerializedInstance *instance) const {
  enter_method;
  
  // Serialize the common event information
  Event::serialize( instance );
  
  // Add our information
  instance->addString(sinkObject);
  instance->addString(sourceObject);
  instance->addUnsigned(flags);
}

Serializable *TutorialMessage::deserialize(SerializedInstance *instance) {
  enter_method;
  
  // Deserialize the basic event information.
  // TODO: move this into the Event class as the end-user has no
  // need for the information.
  VTime *sendTime = dynamic_cast<VTime *>(instance->getSerializable());
  VTime *receiveTime = dynamic_cast<VTime *>(instance->getSerializable());
  unsigned int senderSimManID = instance->getUnsigned();
  unsigned int senderSimObjID = instance->getUnsigned();
  unsigned int receiverSimManID = instance->getUnsigned();
  unsigned int receiverSimObjID = instance->getUnsigned(); 
  unsigned int eventId = instance->getUnsigned();

  // Get the objects associated with the IDs received
  ObjectID sender(senderSimObjID, senderSimManID);
  ObjectID receiver(receiverSimObjID, receiverSimManID);

  // Create the message with this information
  TutorialMessage *message = new TutorialMessage(*sendTime, *receiveTime, 
        sender, receiver, eventId);
  
  // Deserialize our additions
  message->setSinkObject( instance->getString() );
  message->setSourceObject( instance->getString() );
  message->setFlags( instance->getUnsigned() );
  
  // Cleanup
  delete sendTime;
  delete receiveTime;
  
  return message;
}