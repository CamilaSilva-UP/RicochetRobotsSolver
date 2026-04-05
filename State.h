#ifndef STATE_H
#define STATE_H

#include "Board.h"
#include "Robot.h"
#include "Utils.h"

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
  Robot &getRobot(Color color);

  bool operator<(const State &s) const {
    return redRobot != s.redRobot && greenRobot != s.greenRobot &&
           blueRobot != s.blueRobot && yellowRobot != s.yellowRobot;
  }

  bool checkWin(Color targetColor, Position targetPos);

  void print();
};

#endif
