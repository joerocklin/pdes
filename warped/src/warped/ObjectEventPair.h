#ifndef OBJECT_EVENT_PAIR_H_
#define OBJECT_EVENT_PAIR_H_

// See copyright notice in file Copyright in the root directory of this archive.

#include "Event.h"
#include "EventId.h"
#include <utility>
#include <iostream>
using std::pair;
using std::cout;
using std::endl;

namespace warped {

class VTime;
class SimulationObject;

///This is the object type that is actually stored in the Object Queues
class ObjectEventPair
{
public:
	ObjectEventPair(SimulationObject* object, const Event *event)
		: object(object), receiveTime(event->getReceiveTime().clone()), eventId(event->getEventId()), sender(event->getSender()) {}
	~ObjectEventPair()
	{
		delete receiveTime;
	}
	const EventId &getEventId() const
	{
		return eventId;
	}
	const VTime &getReceiveTime() const
	{
		return *receiveTime;
	}
	const ObjectID &getSender() const
	{
		return sender;
	}
	SimulationObject *getObject() const
	{
		return object;
	}
	const bool equals(const Event *e1) const
	{
		if (e1->getEventId() == eventId &&
			e1->getReceiveTime()==*receiveTime &&
			e1->getSender()==sender)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void display()
	{
		cout << "(" <<  *receiveTime  << "," << sender << "," << eventId << ") ";
	}
private:
	SimulationObject *object;
	const VTime *receiveTime;
	const EventId eventId;
	const ObjectID sender;
};
//

}

#endif /* EVENTINFO_H_ */
