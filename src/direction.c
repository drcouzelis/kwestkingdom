#include "direction.h"


const DIRECTION cardinals[4] = { \
  {NORTH, 0, -1, 0, -1}, \
  {SOUTH, 0, 1, 0, 1}, \
  {EAST, 1, 0, 1, 0}, \
  {WEST, -1, 0, -1, 0} \
};

const DIRECTION directions[4] = { \
  {UP, 0, -1, 0, -1}, \
  {DOWN, 0, 1, 0, 1}, \
  {RIGHT, 1, 0, 1, 0}, \
  {LEFT, -1, 0, -1, 0} \
};
