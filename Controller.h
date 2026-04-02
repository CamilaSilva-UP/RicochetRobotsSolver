#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "State.h"
#include "Utils.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Controller {
public:
  State moveRobot(State state, Color color, Direction direction);
};

#endif
