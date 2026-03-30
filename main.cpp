#include "Board.h"
#include "Quadrant.h"
#include "Quadrants.h"
#include "Robot.h"
#include "State.h"
#include "Controller.h"
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

  Robot redRobot, greenRobot, blueRobot, yellowRobot;
  redRobot.setPos({1, 1});      redRobot.setColor(Color::Red);
  greenRobot.setPos({14, 1});   greenRobot.setColor(Color::Green);
  blueRobot.setPos({1, 14});    blueRobot.setColor(Color::Blue);
  yellowRobot.setPos({14, 14}); yellowRobot.setColor(Color::Yellow);

  State state(board, redRobot, greenRobot, blueRobot, yellowRobot);
  Controller controller;

  float cellSize = 60.0f;
  float offset = 20.0f;
  unsigned int winW = (unsigned int)(offset * 2 + board.getWidth() * cellSize);
  unsigned int winH = (unsigned int)(offset * 2 + board.getHeight() * cellSize);
  sf::RenderWindow window(sf::VideoMode({winW, winH}), "Ricochet Robots!");

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Up) {
          controller.moveRobot(state, Color::Red, Direction::UP);
        } else if (keyPressed->code == sf::Keyboard::Key::Down) {
          controller.moveRobot(state, Color::Red, Direction::DOWN);
        } else if (keyPressed->code == sf::Keyboard::Key::Left) {
          controller.moveRobot(state, Color::Red, Direction::LEFT);
        } else if (keyPressed->code == sf::Keyboard::Key::Right) {
          controller.moveRobot(state, Color::Red, Direction::RIGHT);
        }
      }
    }

    window.clear(sf::Color::White);

    state.getBoard().drawBoard(window);
    state.getRobot(Color::Red).draw(window, cellSize, offset);
    state.getRobot(Color::Green).draw(window, cellSize, offset);
    state.getRobot(Color::Blue).draw(window, cellSize, offset);
    state.getRobot(Color::Yellow).draw(window, cellSize, offset);

    window.display();
  }

  return 0;
}
