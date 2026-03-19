#include "Controller.h"

void Controller::moveRedLeft(State state) {
  while (true) {
    Position curPos = state.getRedRobot().getPos();
    Position nextPos = {curPos.x - 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.right) {
        return;
      } else if (wall.pos == nextPos && wall.left) {
        state.getRedRobot().setPos(nextPos);
        return;
      }
    }
    state.getRedRobot().setPos(nextPos);
  }
}
