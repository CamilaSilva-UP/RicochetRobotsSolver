#ifndef BOARD_H
#define BOARD_H

#include "Utils.h"
#include <SFML/Graphics.hpp>
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
  Board();
  Board(int width, int height);

  void addWall(int x, int y, bool up, bool down, bool left, bool right);

  bool isInside(int x, int y) const;

  // this would need more tweaking to be used, since it would need to return 3
  // possibilities (no wall, wall (cant move), or wall (move then stop)) bool
  //
  // hasWall(int x, int y, int dx, int dy) const;

  void drawBoard(sf::RenderWindow &window) const;

  std::vector<Wall> getWalls();
};

#endif
