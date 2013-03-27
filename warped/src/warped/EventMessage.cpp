// See copyright notice in file Copyright in the root directory of this archive.

#include "EventMessage.h"
#include "Event.h"
#include "DeserializerManager.h"

using namespace warped;

Serializable *
EventMessage::deserialize( SerializedInstance *data ){
  unsigned int source = data->getUnsigned();
  unsigned int dest = data->getUnsigned();
  unsigned int incNum = data->getUnsigned();
  Event *event = dynamic_cast<Event *>(data->getSerializable());
  const string gvtInfo = data->getString();

  EventMessage *retval = new EventMessage( source, dest, event, gvtInfo );
  retval->setIncarnationNumber(incNum);
  return retval;
}

const string &
EventMessage::getEventMessageType(){
  static string eventMessageType = "EventMessage";
  return eventMessageType;
}

void 
EventMessage::registerDeserializer(){
  DeserializerManager::instance()->registerDeserializer( getEventMessageType(),
                                                         &EventMessage::deserialize );
}
