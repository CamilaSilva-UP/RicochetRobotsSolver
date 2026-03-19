#ifndef UTILS_H
#define UTILS_H

struct Position {
  int x;
  int y;

  bool operator==(const Position &other) const {
    return x == other.x && y == other.y;
  }
};

enum Color { Red, Green, Blue, Yellow };

#endif
