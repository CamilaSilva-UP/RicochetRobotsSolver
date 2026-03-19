#ifndef STATE_H
#define STATE_H

#include "Board.h"
#include "Robot.h"

class State {
private:
  Board board;
  Robot red;
  Robot green;
  Robot blue;
  Robot yellow;

public:
  State(Board board, Robot red, Robot green, Robot blue, Robot yellow);
  Board getBoard();
  Robot getRedRobot();
  Robot getGreenRobot();
  Robot getBlueRobot();
  Robot getYellowRobot();
};

#endif
