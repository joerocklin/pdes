// See copyright notice in file Copyright in the root directory of this archive.

#include "Event.h"
#include "EventId.h"
#include "SerializedInstance.h"
#include "OptFossilCollManager.h"

using namespace warped;

// No longer using these for optimistic fossil collection.
//bool Event::usingOptFossilCollMan = false;
//OptFossilCollManager *Event::myOptFosColMan = NULL;

Event::~Event(){}

ostream&
warped::operator<<(ostream& os, const Event& event) {
   os << "sender: " << event.getSender() 
      << " receiver: " << event.getReceiver()
      << " sendTime: " << event.getSendTime()
      << " receiveTime: " << event.getReceiveTime()
      << " eventId: " << event.getEventId();
   return(os);
}

bool
warped::operator==(const Event &eve1, const Event &eve2){
  // NOTE: This is used to uniquely identify events for use
  //       in STL containers. Do not use this for comparing
  //       events in lazy cancellation or similar areas. Use
  //       compareEvents instead.
  bool retval = eve1.getSender() == eve2.getSender() &&
                eve1.getEventId() == eve2.getEventId();
  return retval;
}

bool 
Event::compareEvents( const Event *a, const Event *b ){
  bool retval = true;

  if( a->getSender() != b->getSender() ||
      a->getSendTime() != b->getSendTime() ||
      a->getReceiver() != a->getReceiver() ||
      a->getReceiveTime() != b->getReceiveTime() ){
    retval = false;
  }

  return retval;
}

void 
Event::serialize( SerializedInstance *addTo ) const {
  addTo->addSerializable( &getSendTime() );
  addTo->addSerializable( &getReceiveTime() );
  addTo->addUnsigned( getSender().getSimulationManagerID() );
  addTo->addUnsigned( getSender().getSimulationObjectID() );
  addTo->addUnsigned( getReceiver().getSimulationManagerID() );
  addTo->addUnsigned( getReceiver().getSimulationObjectID() );
  addTo->addUnsigned( getEventId().val );
}
