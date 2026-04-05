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

Robot &State::getRobot(Color color) {
  if (color == Color::Red)
    return this->redRobot;
  if (color == Color::Green)
    return this->greenRobot;
  if (color == Color::Blue)
    return this->blueRobot;
  if (color == Color::Yellow)
    return this->yellowRobot;
}

bool State::checkWin(Color targetColor, Position targetPos) {
  Robot robot = getRobot(targetColor);
  Position robotPos = robot.getPos();

  if (robotPos.x == targetPos.x && robotPos.y == targetPos.y) {
    return true;
  }

  return false;
}

void State::print() {
  std::cout << "State:" << std::endl;
  printf("Red Robot: (%d, %d)\n", redRobot.getPos().x, redRobot.getPos().y);
  printf("Green Robot: (%d, %d)\n", greenRobot.getPos().x,
         greenRobot.getPos().y);
  printf("Blue Robot: (%d, %d)\n", blueRobot.getPos().x, blueRobot.getPos().y);
  printf("Yellow Robot: (%d, %d)\n", yellowRobot.getPos().x,
         yellowRobot.getPos().y);
}
