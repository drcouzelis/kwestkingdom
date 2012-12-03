#ifndef TARGETABLE_HEADER
#define TARGETABLE_HEADER


#include "Positionable.h"


class Targetable {
  virtual Positionable *getTarget=0;
};


#endif
