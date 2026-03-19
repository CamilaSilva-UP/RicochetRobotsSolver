#ifndef STATE_H
#define STATE_H

#include "Board.h"
#include "Robot.h"

class State {
private:
  Board board;
  Robot redRobot;
  Robot greenRobot;
  Robot blueRobot;
  Robot yellowRobot;

public:
  State(Board board, Robot redRobot, Robot greenRobot, Robot blueRobot,
        Robot yellowRobot);
  Board getBoard();
  Robot getRedRobot();
  Robot getGreenRobot();
  Robot getBlueRobot();
  Robot getYellowRobot();
};

#endif
