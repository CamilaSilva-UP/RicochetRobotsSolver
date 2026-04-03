#include "Controller.h"

State Controller::moveRobot(State state, Color color, Direction direction) {
  int dx = 0, dy = 0;
  if (direction == Direction::LEFT)
    dx = -1;
  if (direction == Direction::RIGHT)
    dx = 1;
  if (direction == Direction::UP)
    dy = -1;
  if (direction == Direction::DOWN)
    dy = 1;

  Robot &robot = state.getRobot(color);

  while (true) {
    Position curPos = robot.getPos();
    Position nextPos = {curPos.x + dx, curPos.y + dy};

    if (nextPos.x < 0 || nextPos.x >= 16 || nextPos.y < 0 || nextPos.y >= 16) {
      break;
    }

    bool stopBeforeEntering = false;
    bool stopAfterEntering = false;

    for (Wall wall : state.getBoard().getWalls()) {
      // Parede na célula atual bloqueia a saída
      if (wall.pos == curPos) {
        if (direction == Direction::LEFT  && wall.left)   stopBeforeEntering = true;
        if (direction == Direction::RIGHT && wall.right)  stopBeforeEntering = true;
        if (direction == Direction::UP    && wall.up)     stopBeforeEntering = true;
        if (direction == Direction::DOWN  && wall.down)   stopBeforeEntering = true;
      }
      // Parede na célula de destino bloqueia a entrada
      if (wall.pos == nextPos) {
        if (direction == Direction::LEFT  && wall.right)  stopBeforeEntering = true;
        if (direction == Direction::RIGHT && wall.left)   stopBeforeEntering = true;
        if (direction == Direction::UP    && wall.down)   stopBeforeEntering = true;
        if (direction == Direction::DOWN  && wall.up)     stopBeforeEntering = true;
        if (direction == Direction::LEFT  && wall.left)   stopAfterEntering = true;
        if (direction == Direction::RIGHT && wall.right)  stopAfterEntering = true;
        if (direction == Direction::UP    && wall.up)     stopAfterEntering = true;
        if (direction == Direction::DOWN  && wall.down)   stopAfterEntering = true;
      }
    }

    // Colisão com outro robot
    for (Color c : {Color::Red, Color::Green, Color::Blue, Color::Yellow}) {
      if (c != color && state.getRobot(c).getPos() == nextPos) {
        stopBeforeEntering = true;
        break;
      }
    }

    if (stopBeforeEntering) {
      return state;
    }

    robot.setPos(nextPos);

    if (stopAfterEntering) {
      return state;
    }
  }
  return state;
}
