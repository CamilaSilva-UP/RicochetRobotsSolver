#include "Board.h"
#include "Quadrant.h"
#include "Quadrants.h"
#include "Robot.h"
#include "State.h"
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>

// 7-segment display: segments = {top, top-right, bottom-right, bottom, bottom-left, top-left, middle}
static const bool DIGITS[10][7] = {
  {true,  true,  true,  true,  true,  true,  false}, // 0
  {false, true,  true,  false, false, false, false}, // 1
  {true,  true,  false, true,  true,  false, true},  // 2
  {true,  true,  true,  true,  false, false, true},  // 3
  {false, true,  true,  false, false, true,  true},  // 4
  {true,  false, true,  true,  false, true,  true},  // 5
  {true,  false, true,  true,  true,  true,  true},  // 6
  {true,  true,  true,  false, false, false, false}, // 7
  {true,  true,  true,  true,  true,  true,  true},  // 8
  {true,  true,  true,  true,  false, true,  true},  // 9
};

struct Target {
    Position pos;
    Color color;
};

void drawDigit(sf::RenderWindow& window, int digit, float x, float y, float h) {
  float sw = h * 0.12f; // segment thickness
  float sl = h * 0.42f; // segment length
  float gap = sw * 0.3f;
  sf::Color on(30, 30, 30);
  sf::Color off(210, 210, 210);

  auto seg = [&](sf::RectangleShape& s, sf::Color c) {
    s.setFillColor(c);
    window.draw(s);
  };

  // top
  sf::RectangleShape top(sf::Vector2f(sl, sw));
  top.setPosition({x + gap, y});
  seg(top, DIGITS[digit][0] ? on : off);

  // top-right
  sf::RectangleShape tr(sf::Vector2f(sw, sl));
  tr.setPosition({x + gap + sl, y + gap});
  seg(tr, DIGITS[digit][1] ? on : off);

  // bottom-right
  sf::RectangleShape br(sf::Vector2f(sw, sl));
  br.setPosition({x + gap + sl, y + gap + sl + gap});
  seg(br, DIGITS[digit][2] ? on : off);

  // bottom
  sf::RectangleShape bot(sf::Vector2f(sl, sw));
  bot.setPosition({x + gap, y + 2 * (gap + sl)});
  seg(bot, DIGITS[digit][3] ? on : off);

  // bottom-left
  sf::RectangleShape bl(sf::Vector2f(sw, sl));
  bl.setPosition({x, y + gap + sl + gap});
  seg(bl, DIGITS[digit][4] ? on : off);

  // top-left
  sf::RectangleShape tl(sf::Vector2f(sw, sl));
  tl.setPosition({x, y + gap});
  seg(tl, DIGITS[digit][5] ? on : off);

  // middle
  sf::RectangleShape mid(sf::Vector2f(sl, sw));
  mid.setPosition({x + gap, y + gap + sl});
  seg(mid, DIGITS[digit][6] ? on : off);
}

void drawNumber(sf::RenderWindow& window, int number, float x, float y, float digitH) {
  std::string s = std::to_string(number);
  float digitW = digitH * 0.6f;
  float spacing = digitH * 0.1f;
  for (int i = 0; i < (int)s.size(); i++) {
    drawDigit(window, s[i] - '0', x + i * (digitW + spacing), y, digitH);
  }
}

int main() {
  Board board(16, 16);

  auto quadrants = getQuadrants();
  std::shuffle(quadrants.begin(), quadrants.end(), std::mt19937{std::random_device{}()});

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

  std::vector<Position> validPositions;

  for (auto wall : board.getWalls()) {
      if ((wall.pos.x == 7 || wall.pos.x == 8) && (wall.pos.y == 7 || wall.pos.y == 8)) {
          continue; 
      }
      validPositions.push_back(wall.pos);
  }

  std::shuffle(validPositions.begin(), validPositions.end(), std::mt19937{std::random_device{}()});

  std::vector<Target> allTargets = {
      {validPositions[0], Color::Red},
      {validPositions[1], Color::Green},
      {validPositions[2], Color::Blue},
      {validPositions[3], Color::Yellow}
  };

  std::shuffle(allTargets.begin(), allTargets.end(), std::mt19937{std::random_device{}()});

  float cellSize = 60.0f;
  float offset = 20.0f;
  float panelWidth = 200.0f;
  unsigned int winW = (unsigned int)(offset * 2 + board.getWidth() * cellSize + panelWidth);
  unsigned int winH = (unsigned int)(offset * 2 + board.getHeight() * cellSize);
  sf::RenderWindow window(sf::VideoMode({winW, winH}), "Ricochet Robots!");

  int moveCount = 0;
  Color selectedColor = Color::Red;

  // Botões: posições e cores
  float panelX = offset * 2 + board.getWidth() * cellSize;
  float btnW = 160.0f;
  float btnH = 50.0f;
  float btnSpacing = 10.0f;
  float btnsY = 200.0f;
  std::vector<Color> btnColors = {Color::Red, Color::Green, Color::Blue, Color::Yellow};
  std::vector<sf::Color> sfColors = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseClick->button == sf::Mouse::Button::Left) {
          float mx = (float)mouseClick->position.x;
          float my = (float)mouseClick->position.y;
          for (int i = 0; i < 4; i++) {
            float by = btnsY + i * (btnH + btnSpacing);
            float bx = panelX + 20.0f;
            if (mx >= bx && mx <= bx + btnW && my >= by && my <= by + btnH)
              selectedColor = btnColors[i];
          }
        }
      }

      if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        State prevState = state;
        if (keyPressed->code == sf::Keyboard::Key::Up)
          state = controller.moveRobot(state, selectedColor, Direction::UP);
        else if (keyPressed->code == sf::Keyboard::Key::Down)
          state = controller.moveRobot(state, selectedColor, Direction::DOWN);
        else if (keyPressed->code == sf::Keyboard::Key::Left)
          state = controller.moveRobot(state, selectedColor, Direction::LEFT);
        else if (keyPressed->code == sf::Keyboard::Key::Right)
          state = controller.moveRobot(state, selectedColor, Direction::RIGHT);

        if (!(state.getRobot(selectedColor).getPos() == prevState.getRobot(selectedColor).getPos())){
          moveCount++;

          for (size_t i = 0; i < allTargets.size(); i++) {
              if (state.checkWin(allTargets[i].color, allTargets[i].pos)) {
                std::cout << "You reached the target in " << moveCount << " moves" << std::endl;
                moveCount = 0;      
                break;
              }
          }
        }
      }
    }

    window.clear(sf::Color::White);

    state.getBoard().drawBoard(window);

    float targetSize = cellSize;
    
    for (const auto& target : allTargets) {
        sf::RectangleShape targetShape(sf::Vector2f(targetSize, targetSize));
        
        float tx = offset + target.pos.x * cellSize;
        float ty = offset + target.pos.y * cellSize;
        targetShape.setPosition({tx, ty});

        if (target.color == Color::Red)         targetShape.setFillColor(sf::Color(255, 0, 0, 150));
        else if (target.color == Color::Green)  targetShape.setFillColor(sf::Color(0, 255, 0, 150));
        else if (target.color == Color::Blue)   targetShape.setFillColor(sf::Color(0, 0, 255, 150));
        else if (target.color == Color::Yellow) targetShape.setFillColor(sf::Color(255, 255, 0, 150));

        window.draw(targetShape);
    }

    state.getRobot(Color::Red).draw(window, cellSize, offset);
    state.getRobot(Color::Green).draw(window, cellSize, offset);
    state.getRobot(Color::Blue).draw(window, cellSize, offset);
    state.getRobot(Color::Yellow).draw(window, cellSize, offset);

    // Painel lateral
    sf::RectangleShape panel(sf::Vector2f(panelWidth, (float)winH));
    panel.setPosition({panelX, 0});
    panel.setFillColor(sf::Color(240, 240, 240));
    window.draw(panel);

    // Score
    sf::RectangleShape labelBar(sf::Vector2f(120.0f, 6.0f));
    labelBar.setFillColor(sf::Color(100, 100, 100));
    labelBar.setPosition({panelX + 20.0f, 30.0f});
    window.draw(labelBar);

    drawNumber(window, moveCount, panelX + 20.0f, 50.0f, 80.0f);

    // Botões de seleção de robot
    for (int i = 0; i < 4; i++) {
      float bx = panelX + 20.0f;
      float by = btnsY + i * (btnH + btnSpacing);

      if (btnColors[i] == selectedColor) {
        sf::RectangleShape outline(sf::Vector2f(btnW + 6.0f, btnH + 6.0f));
        outline.setPosition({bx - 3.0f, by - 3.0f});
        outline.setFillColor(sf::Color::Black);
        window.draw(outline);
      }

      sf::RectangleShape btn(sf::Vector2f(btnW, btnH));
      btn.setPosition({bx, by});
      btn.setFillColor(sfColors[i]);
      window.draw(btn);
    }

    window.display();
  }

  return 0;
}
