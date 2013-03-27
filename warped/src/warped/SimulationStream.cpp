// See copyright notice in file Copyright in the root directory of this archive.

#include "SimulationStream.h"

using namespace warped;

ostream& nl(ostream& os){
   ((SimulationStream &)os).flush();
   return os;
}


