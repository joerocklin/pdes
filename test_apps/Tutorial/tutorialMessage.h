#ifndef TUTORIAL_MESSAGE_H
#define TUTORIAL_MESSAGE_H

#include <warped/DefaultEvent.h>
#include <warped/SerializedInstance.h>

#include <iostream>
using namespace std;

enum tcp_flag {
  NS  =   1,
  CWR =   2,
  ECE =   4,
  URG =   8,
  ACK =  16,
  PSH =  32,
  RST =  64,
  SYN = 128,
  FIN = 256,
};

class TutorialMessage : public DefaultEvent {
public:
  TutorialMessage(const VTime &sendTime,
                  const VTime &recvTime,
                  SimulationObject *sender,
                  SimulationObject *receiver);
                  
  const string &getDataType() const;
  bool eventCompare(const Event* event);
  unsigned int getEventSize() const { enter_method; return sizeof(TutorialMessage); };
  
  void serialize(SerializedInstance *instance) const;
  static Serializable *deserialize(SerializedInstance* instance);
  
  // Getters
  const string getSinkObject() const { return this->sinkObject; }
  const string getSourceObject() const { return this->sourceObject; }
  const unsigned int getFlags() const { return this->flags; }
  const bool getFlag(tcp_flag flag) const { return this->flags & flag; }
  
  // Setters
  void setSinkObject(string id) { this->sinkObject = id; }
  void setSourceObject(string id) { this->sourceObject = id; }
  void setFlags(unsigned int flags) { this->flags = flags; }
  void setFlag(tcp_flag flag) { this->flags = this->flags | flag; }
  
private:
  string sourceObject;
  string sinkObject;
  unsigned int flags;
  
  // Constructor called by deserializer.
  TutorialMessage(const VTime &sendTime,
                  const VTime &recvTime,
                  const ObjectID &sender,
                  const ObjectID &receiver,
                  unsigned int initEventId);
  static const string &getTutorialMessageDataType();
  
};

#endif