#include "State.h"

State::State(Board board, Robot redRobot, Robot greenRobot, Robot blueRobot,
             Robot yellowRobot) {
  this->board = board;
  this->redRobot = redRobot;
  this->greenRobot = greenRobot;
  this->blueRobot = blueRobot;
  this->yellowRobot = yellowRobot;
}

Board State::getBoard() { return this->board; }
Robot State::getRedRobot() { return this->redRobot; }
Robot State::getGreenRobot() { return this->greenRobot; }
Robot State::getBlueRobot() { return this->blueRobot; }
Robot State::getYellowRobot() { return this->blueRobot; }
