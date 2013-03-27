// See copyright notice in file Copyright in the root directory of this archive.

#include "Configurable.h"

using namespace warped;

vector<Configurer *> &
Configurable::getConfigurersEmpty(){
  static vector<Configurer *> &retval = *new vector<Configurer *>;
  return retval;
}
