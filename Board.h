#ifndef BOARD_H
#define BOARD_H

#include "Utils.h"
#include <iostream>
#include <vector>

struct Wall {
  Position pos;
  bool up;
  bool down;
  bool left;
  bool right;
};

class Board {
private:
  int width;
  int height;
  std::vector<Wall> walls;

public:
  Board(int width, int height);

  void addWall(int x, int y, bool up, bool down, bool left, bool right);

  bool isInside(int x, int y) const;

  bool hasWall(int x, int y, int dx, int dy) const;

  void drawBoard() const;

  std::vector<Wall> getWalls();
};

#endif
