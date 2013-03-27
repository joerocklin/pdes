// See copyright notice in file Copyright in the root directory of this archive.

#include "FlatState.h"
#include <string.h>

using namespace warped;

FlatState::FlatState(){}

FlatState::~FlatState(){}

void
FlatState::copyState(const State* state) {
  memcpy(this, state, ((FlatState *)state)->getSize());
}
