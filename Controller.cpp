#include "Controller.h"

void Controller::moveRobot(State &state, Color color, Direction direction) {
  int dx = 0, dy = 0;
  if(direction == Direction::LEFT) dx = -1;
  if(direction == Direction::RIGHT) dx = 1;
  if(direction == Direction::UP) dy = -1;
  if(direction == Direction::DOWN) dy = 1;

  Robot& robot = state.getRobot(color);
  
  while (true) {
    Position curPos = robot.getPos();
    Position nextPos = {curPos.x + dx, curPos.y + dy};

    bool stopBeforeEntering = false;
    bool stopAfterEntering = false;

    for (Wall wall : state.getBoard().getWalls()) {
      if (wall.pos == nextPos) {
        if (direction == Direction::LEFT){
          if(wall.right) stopBeforeEntering = true;
          else if (wall.left) stopAfterEntering = true;
        }
        else if (direction == Direction::RIGHT){
          if (wall.left) stopBeforeEntering = true;
          else if (wall.right) stopAfterEntering = true;
        }
        else if (direction == Direction::UP){
          if (wall.down) stopBeforeEntering = true;
          else if (wall.up) stopAfterEntering = true;
        }
        else if (direction == Direction::DOWN){
          if (wall.up) stopBeforeEntering = true;
          else if (wall.down) stopAfterEntering = true;
        }
      }
    }

    if(stopBeforeEntering){
      return;
    }

    robot.setPos(nextPos);

    if(stopAfterEntering){
      return;
    }
  }
}