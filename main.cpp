#include "Board.h"
#include "Quadrant.h"
#include "Quadrants.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>

int main() {
  Board board(16, 16);

  // Get random 4 out of the quadrants in quadrants.cpp
  auto quadrants = getQuadrants();
  std::shuffle(quadrants.begin(), quadrants.end(), std::mt19937{std::random_device{}()});

  // Each quadrant gets rotated in order to be put in the right form
  std::vector<std::pair<int, int>> positions = {{0, 0}, {8, 0}, {8, 8}, {0, 8}};
  std::vector<int> rotations = {0, 90, 180, 270};

  for (int i = 0; i < 4 && i < (int)quadrants.size(); i++) {
    board.placeQuadrant(rotateQuadrant(quadrants[i], rotations[i]), positions[i].first, positions[i].second);
  }

  float cellSize = 60.0f;
  float offset = 20.0f;
  unsigned int winW = (unsigned int)(offset * 2 + board.getWidth() * cellSize);
  unsigned int winH = (unsigned int)(offset * 2 + board.getHeight() * cellSize);
  sf::RenderWindow window(sf::VideoMode({winW, winH}), "Ricochet Robots!");

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear(sf::Color::White);

    board.drawBoard(window);

    window.display();
  }

  return 0;
}
