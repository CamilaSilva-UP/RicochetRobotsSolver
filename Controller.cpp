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

void Controller::moveGreenLeft(State state) {
  while (true) {
    Position curPos = state.getGreenRobot().getPos();
    Position nextPos = {curPos.x - 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.right) {
        return;
      } else if (wall.pos == nextPos && wall.left) {
        state.getGreenRobot().setPos(nextPos);
        return;
      }
    }
    state.getGreenRobot().setPos(nextPos);
  }
}

void Controller::moveGreenRight(State state) {
  while (true) {
    Position curPos = state.getGreenRobot().getPos();
    Position nextPos = {curPos.x + 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.left) {
        return;
      } else if (wall.pos == nextPos && wall.right) {
        state.getGreenRobot().setPos(nextPos);
        return;
      }
    }
    state.getGreenRobot().setPos(nextPos);
  }
}

void Controller::moveGreenUp(State state) {
  while (true) {
    Position curPos = state.getGreenRobot().getPos();
    Position nextPos = {curPos.x, curPos.y - 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.down) {
        return;
      } else if (wall.pos == nextPos && wall.up) {
        state.getGreenRobot().setPos(nextPos);
        return;
      }
    }
    state.getGreenRobot().setPos(nextPos);
  }
}

void Controller::moveGreenDown(State state) {
  while (true) {
    Position curPos = state.getGreenRobot().getPos();
    Position nextPos = {curPos.x, curPos.y + 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.up) {
        return;
      } else if (wall.pos == nextPos && wall.down) {
        state.getGreenRobot().setPos(nextPos);
        return;
      }
    }
    state.getGreenRobot().setPos(nextPos);
  }
}

void Controller::moveBlueLeft(State state) {
  while (true) {
    Position curPos = state.getBlueRobot().getPos();
    Position nextPos = {curPos.x - 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.right) {
        return;
      } else if (wall.pos == nextPos && wall.left) {
        state.getBlueRobot().setPos(nextPos);
        return;
      }
    }
    state.getBlueRobot().setPos(nextPos);
  }
}

void Controller::moveBlueRight(State state) {
  while (true) {
    Position curPos = state.getBlueRobot().getPos();
    Position nextPos = {curPos.x + 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.left) {
        return;
      } else if (wall.pos == nextPos && wall.right) {
        state.getBlueRobot().setPos(nextPos);
        return;
      }
    }
    state.getBlueRobot().setPos(nextPos);
  }
}

void Controller::moveBlueUp(State state) {
  while (true) {
    Position curPos = state.getBlueRobot().getPos();
    Position nextPos = {curPos.x, curPos.y - 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.down) {
        return;
      } else if (wall.pos == nextPos && wall.up) {
        state.getBlueRobot().setPos(nextPos);
        return;
      }
    }
    state.getBlueRobot().setPos(nextPos);
  }
}

void Controller::moveBlueDown(State state) {
  while (true) {
    Position curPos = state.getBlueRobot().getPos();
    Position nextPos = {curPos.x, curPos.y + 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.up) {
        return;
      } else if (wall.pos == nextPos && wall.down) {
        state.getBlueRobot().setPos(nextPos);
        return;
      }
    }
    state.getBlueRobot().setPos(nextPos);
  }
}

void Controller::moveYellowLeft(State state) {
  while (true) {
    Position curPos = state.getYellowRobot().getPos();
    Position nextPos = {curPos.x - 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.right) {
        return;
      } else if (wall.pos == nextPos && wall.left) {
        state.getYellowRobot().setPos(nextPos);
        return;
      }
    }
    state.getYellowRobot().setPos(nextPos);
  }
}

void Controller::moveYellowRight(State state) {
  while (true) {
    Position curPos = state.getYellowRobot().getPos();
    Position nextPos = {curPos.x + 1, curPos.y};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.left) {
        return;
      } else if (wall.pos == nextPos && wall.right) {
        state.getYellowRobot().setPos(nextPos);
        return;
      }
    }
    state.getYellowRobot().setPos(nextPos);
  }
}

void Controller::moveYellowUp(State state) {
  while (true) {
    Position curPos = state.getYellowRobot().getPos();
    Position nextPos = {curPos.x, curPos.y - 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.down) {
        return;
      } else if (wall.pos == nextPos && wall.up) {
        state.getYellowRobot().setPos(nextPos);
        return;
      }
    }
    state.getYellowRobot().setPos(nextPos);
  }
}

void Controller::moveYellowDown(State state) {
  while (true) {
    Position curPos = state.getYellowRobot().getPos();
    Position nextPos = {curPos.x, curPos.y + 1};

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos && wall.up) {
        return;
      } else if (wall.pos == nextPos && wall.down) {
        state.getYellowRobot().setPos(nextPos);
        return;
      }
    }
    state.getYellowRobot().setPos(nextPos);
  }
}
