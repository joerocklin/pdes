#ifndef DEFAULTTIMEWARPEVENTCONTONEANTIMSG_H_
#define DEFAULTTIMEWARPEVENTCONTONEANTIMSG_H_

// See copyright notice in file Copyright in the root directory of this archive.

#include "DefaultTimeWarpEventContainer.h"

namespace warped {

/**
    This class is the same as the base DefaultTimeWarpEventContainter
    class except for the remove function, which is modified to handle
    the one anti-message optimization.
*/
class DefaultTimeWarpEventContOneAntiMsg : public DefaultTimeWarpEventContainer {
public:
   DefaultTimeWarpEventContOneAntiMsg(){}
   ~DefaultTimeWarpEventContOneAntiMsg(){}

   bool handleAntiMessage( SimulationObject *reclaimer, const NegativeEvent *eventToRemove );

};

}

#endif
