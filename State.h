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

  bool operator==(const State &s) const {
    return redRobot == s.redRobot && greenRobot == s.greenRobot &&
           blueRobot == s.blueRobot && yellowRobot == s.yellowRobot;
  }

  bool operator<(const State &s) const {
    if (redRobot.getPos() < s.redRobot.getPos()) return true;
    if (s.redRobot.getPos() < redRobot.getPos()) return false;

    if (greenRobot.getPos() < s.greenRobot.getPos()) return true;
    if (s.greenRobot.getPos() < greenRobot.getPos()) return false;

    if (blueRobot.getPos() < s.blueRobot.getPos()) return true;
    if (s.blueRobot.getPos() < blueRobot.getPos()) return false;

    return yellowRobot.getPos() < s.yellowRobot.getPos();
  }

  bool checkWin(Color targetColor, Position targetPos);

  void print();
};

#endif
