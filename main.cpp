#include <iostream>
#include <set>
#include "Board.h"

struct position {
  int x, y;
};

bool operator==(const position &pos1, const position &pos2) {
  if (pos1.x == pos2.x && pos1.y == pos2.y)
    return true;
  return false;
}

struct wall {
  position pos;
  bool up;
  bool down;
  bool left;
  bool right;
};

class boardState {
public:
  position redRobot;
  position greenRobot;
  position blueRobot;
  position yellowRobot;

  std::set<wall> walls;

  boardState(position red, position green, position blue, position yellow,
             std::set<wall> walls) {
    redRobot = red;
    greenRobot = green;
    blueRobot = blue;
    yellowRobot = yellow;
    this->walls = walls;
  }
};

void moveRedLeft(boardState state) {
  while (true) {
    position nextPos = {state.redRobot.x - 1, state.redRobot.y};
    bool canMove = true;
    bool lastMove = false;

    for (auto wall : state.walls) {
      if (wall.pos == nextPos) {
        if (wall.right) {
          canMove = false;
          break;
        } else {
          lastMove = true;
          break;
        }
      }
    }

    if (canMove) {
      state.redRobot = nextPos;
      if (lastMove)
        return;
    } else
      return;
  }
}
void moveRedRight(boardState state) {}
void moveRedUp(boardState state) {}
void moveRedDown(boardState state) {}

void moveGreenLeft(boardState state) {}
void moveGreenRight(boardState state) {}
void moveGreenUp(boardState state) {}
void moveGreenDown(boardState state) {}

void moveBlueLeft(boardState state) {}
void moveBlueRight(boardState state) {}
void moveBlueUp(boardState state) {}
void moveBlueDown(boardState state) {}

void moveYellowLeft(boardState state) {}
void moveYellowRight(boardState state) {}
void moveYellowUp(boardState state) {}
void moveYellowDown(boardState state) {}

int main() {
    Board board(5, 5);
    board.addWall(0, 0, false, true, false, true);
    board.addWall(2, 2, true, false, false, false);

    board.drawBoard();

    return 0;
}