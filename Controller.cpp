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

void Controller::moveRedRight(State state) {
  while (true) {
    Position curPos = state.getRedRobot().getPos();
    Position nextPos = {curPos.x + 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.left) {
        return;
      } else if (wall.pos == nextPos && wall.right) {
        state.getRedRobot().setPos(nextPos);
        return;
      }
    }
    state.getRedRobot().setPos(nextPos);
  }
}

void Controller::moveRedUp(State state) {
  while (true) {
    Position curPos = state.getRedRobot().getPos();
    Position nextPos = {curPos.x, curPos.y - 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.down) {
        return;
      } else if (wall.pos == nextPos && wall.up) {
        state.getRedRobot().setPos(nextPos);
        return;
      }
    }
    state.getRedRobot().setPos(nextPos);
  }
}

void Controller::moveRedDown(State state) {
  while (true) {
    Position curPos = state.getRedRobot().getPos();
    Position nextPos = {curPos.x, curPos.y + 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.up) {
        return;
      } else if (wall.pos == nextPos && wall.down) {
        state.getRedRobot().setPos(nextPos);
        return;
      }
    }
    state.getRedRobot().setPos(nextPos);
  }
}
