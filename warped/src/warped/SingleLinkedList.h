#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

// See copyright notice in file Copyright in the root directory of this archive.

#include <queue>
#include "Event.h"
#include "EventSet.h"

using std::priority_queue;

namespace warped {

struct compareEvents {
  bool operator()( const Event *a, const Event *b ) {
    return ((a->getReceiveTime() == b->getReceiveTime()) ?
	    ((a->getReceiver() > b->getReceiver()) ? false : true) :
	    ((a->getReceiveTime() > b->getReceiveTime())));
  }
};

/** The SingleLinkedList class.

    The SingleLinkedList class is an implementation of the abstract
    EventSet class. It implements a single linked list data structure
    that is used as an event queue in a sequential simulation. Since
    the sequential simulation processes events in a strict lowest
    timestamp first order, the SingleLinkedList class inherits the
    semantics of a priority queue. The priority queue accepts as
    template arguments, the element type (Event*), the sequence type
    (vector or list), and a comparison function object
    (compareEvents).

*/
class SingleLinkedList : public priority_queue<const Event*, 
			 vector<const Event*>,
                         compareEvents>, public EventSet {
public:

  /**@name Public Class Methods of SingleLinkedList. */
  //@{

  /// Default Constructor
  SingleLinkedList();

  /// Destructor.
  ~SingleLinkedList();

  /** Insert an event into the event set.

      @param event Pointer to the event to be inserted.
  */
  void insert( const Event *event);

  /** Return a reference to the first event and remove from the event set.

      @return A reference to the first event in the event set.
  */
  const Event *getEvent();

  /** Return reference to first event without removing it from the event set.

      @return A reference to the first event in the event set.
  */
  const Event *peekEvent();

  /// Delete any old, unwanted events.
  void cleanUp();

  virtual void configure( SimulationConfiguration & ){}

  static const string &getType();

  //@} // End of Public Class Methods of SingleLinkedList

  /**@name Public Class Attributes of SingleLinkedList. */
  //@{

  /// The comparison function object used by priority_queue

  //@} // End of Public Class Attributes of SingleLinkedList. */
   
private:

  /**@name Private Class Attributes of SingleLinkedList. */
  //@{

  /// List of processedEvents that can be deleted.
  vector<const Event *> *processedEvents;

  //@} // End of  Private Class Attributes of SingleLinkedList
};

}

#endif
