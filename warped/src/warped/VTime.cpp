// See copyright notice in file Copyright in the root directory of this archive.

#include "VTime.h"
using namespace warped;

VTime::~VTime() {}

const VTime &  
VTime::operator= (const VTime &from){
  std::cerr << "VTime::operator= called, aborting" << std::endl;
  abort();
}
