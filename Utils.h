#ifndef UTILS_H
#define UTILS_H

struct Position {
  int x;
  int y;

  bool operator==(const Position &other) const {
    return x == other.x && y == other.y;
  }
};

struct Wall {
  Position pos;
  bool up;
  bool down;
  bool left;
  bool right;
};

enum Color { Red, Green, Blue, Yellow };

struct Target {
  Position pos;
  Color color;
};

#endif
