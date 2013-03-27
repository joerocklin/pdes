#ifndef LOCALNEGATIVEEVENTMESSAGE_H_
#define LOCALNEGATIVEEVENTMESSAGE_H_

// See copyright notice in file Copyright in the root directory of this archive.

#include "LocalKernelMessage.h"
#include "NegativeEventMessage.h"
#include "NegativeEvent.h"
#include "Event.h"
#include <vector>

namespace warped {

class LocalNegativeEventMessage : public LocalKernelMessage
{
private:
	vector<const NegativeEvent *> *negativeEvents;
public:
	LocalNegativeEventMessage(const vector<const NegativeEvent *> &negEvents, local_kernel_message_type messageType, SimulationObject *object)
		: negativeEvents(new vector<const NegativeEvent *>(negEvents.begin(), negEvents.end())),
		  LocalKernelMessage(messageType, object, negEvents[0]->getReceiveTime().clone()) {}

	~LocalNegativeEventMessage()
	{
		delete negativeEvents;
	}

	const vector<const NegativeEvent*> &getNegativeEvents()
	{
		return *negativeEvents;
	}
};

}

#endif /* LOCALNEGATIVEEVENTMESSAGE_H_ */
