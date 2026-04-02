#ifndef ROBOT_H
#define ROBOT_H

#include "Utils.h"
#include <SFML/Graphics.hpp>

class Robot {
private:
  Position pos;
  Color color;

public:
  Position getPos();
  void setPos(Position pos);
  void setColor(Color c);
  void draw(sf::RenderWindow &window, float cellSize, float offset);

  bool operator!=(const Robot &r) const { return !(pos == r.pos); }
};

#endif
