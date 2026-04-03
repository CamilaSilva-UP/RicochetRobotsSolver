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

Robot& State::getRobot(Color color) {
  if (color == Color::Red) return this->redRobot;
  if (color == Color::Green) return this->greenRobot;
  if (color == Color::Blue) return this->blueRobot;
  if (color == Color::Yellow) return this->yellowRobot; 
}


bool State::checkWin(Color targetColor, Position targetPos) {
    Robot robot = getRobot(targetColor); 
    Position robotPos = robot.getPos();

    if (robotPos.x == targetPos.x && robotPos.y == targetPos.y) {
        return true;
    }

    return false; 
}
