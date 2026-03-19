#ifndef ROBOT_H
#define ROBOT_H

#include "Utils.h"

class Robot {
private:
  Position pos;
  Color color;

public:
  Position getPos();
  void setPos(Position pos);
};

#endif
