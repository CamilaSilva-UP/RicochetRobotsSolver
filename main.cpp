#include "Board.h"
#include "Controller.h"
#include "Menu.h"
#include "Quadrant.h"
#include "Quadrants.h"
#include "Robot.h"
#include "Solver.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>
#include <random>
#include <unistd.h>

//contador logic
static const bool DIGITS[10][7] = {
    {true, true, true, true, true, true, false},     // 0
    {false, true, true, false, false, false, false}, // 1
    {true, true, false, true, true, false, true},    // 2
    {true, true, true, true, false, false, true},    // 3
    {false, true, true, false, false, true, true},   // 4
    {true, false, true, true, false, true, true},    // 5
    {true, false, true, true, true, true, true},     // 6
    {true, true, true, false, false, false, false},  // 7
    {true, true, true, true, true, true, true},      // 8
    {true, true, true, true, false, true, true},     // 9
};

void drawDigit(sf::RenderWindow &window, int digit, float x, float y, float h) {
  float sw = h * 0.12f; // segment thickness
  float sl = h * 0.42f; // segment length
  float gap = sw * 0.3f;
  sf::Color on(30, 30, 30);
  sf::Color off(210, 210, 210);

  auto seg = [&](sf::RectangleShape &s, sf::Color c) {
    s.setFillColor(c);
    window.draw(s);
  };

  //  -
  // | |
  //  -
  // | |
  //  -
  //
  //  1
  // 6 2
  //  7
  // 5 3
  //  4


  sf::RectangleShape top(sf::Vector2f(sl, sw));
  top.setPosition({x + gap, y});
  seg(top, DIGITS[digit][0] ? on : off);

  sf::RectangleShape tr(sf::Vector2f(sw, sl));
  tr.setPosition({x + gap + sl, y + gap});
  seg(tr, DIGITS[digit][1] ? on : off);

  sf::RectangleShape br(sf::Vector2f(sw, sl));
  br.setPosition({x + gap + sl, y + gap + sl + gap});
  seg(br, DIGITS[digit][2] ? on : off);

  sf::RectangleShape bot(sf::Vector2f(sl, sw));
  bot.setPosition({x + gap, y + 2 * (gap + sl)});
  seg(bot, DIGITS[digit][3] ? on : off);

  sf::RectangleShape bl(sf::Vector2f(sw, sl));
  bl.setPosition({x, y + gap + sl + gap});
  seg(bl, DIGITS[digit][4] ? on : off);

  sf::RectangleShape tl(sf::Vector2f(sw, sl));
  tl.setPosition({x, y + gap});
  seg(tl, DIGITS[digit][5] ? on : off);

  sf::RectangleShape mid(sf::Vector2f(sl, sw));
  mid.setPosition({x + gap, y + gap + sl});
  seg(mid, DIGITS[digit][6] ? on : off);
}

void drawNumber(sf::RenderWindow &window, int number, float x, float y,
                float digitH) {
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
  std::shuffle(quadrants.begin(), quadrants.end(),
               std::mt19937{std::random_device{}()});

  std::vector<std::pair<int, int>> positions = {{0, 0}, {8, 0}, {8, 8}, {0, 8}};
  std::vector<int> rotations = {0, 90, 180, 270};

  for (int i = 0; i < 4 && i < (int)quadrants.size(); i++) {
    board.placeQuadrant(rotateQuadrant(quadrants[i], rotations[i]),
                        positions[i].first, positions[i].second);
  }

  Robot redRobot, greenRobot, blueRobot, yellowRobot;
  redRobot.setPos({1, 1});
  redRobot.setColor(Color::Red);
  greenRobot.setPos({14, 1});
  greenRobot.setColor(Color::Green);
  blueRobot.setPos({1, 14});
  blueRobot.setColor(Color::Blue);
  yellowRobot.setPos({14, 14});
  yellowRobot.setColor(Color::Yellow);

  State state(board, redRobot, greenRobot, blueRobot, yellowRobot);
  State initialState = state;
  Controller controller;

  std::vector<Position> validPositions;

  for (auto wall : board.getWalls()) {
    if (((wall.pos.x == 7 || wall.pos.x == 8) &&
         (wall.pos.y == 7 || wall.pos.y == 8)) ||
        ((wall.pos.x == 1 || wall.pos.x == 14) &&
         (wall.pos.y == 1 || wall.pos.y == 14))) {
      continue;
    }
    bool up = board.hasWall(wall.pos.x, wall.pos.y, 0, -1);
    bool down = board.hasWall(wall.pos.x, wall.pos.y, 0, 1);
    bool left = board.hasWall(wall.pos.x, wall.pos.y, -1, 0);
    bool right = board.hasWall(wall.pos.x, wall.pos.y, 1, 0);

    if ((up && left) || (up && right) || (down && left) || (down && right)) {
      validPositions.push_back(wall.pos);
    }
  }

  std::shuffle(validPositions.begin(), validPositions.end(),
               std::mt19937{std::random_device{}()});

  std::vector<Target> allTargets = {{validPositions[0], Color::Red},
                                    {validPositions[1], Color::Green},
                                    {validPositions[2], Color::Blue},
                                    {validPositions[3], Color::Yellow}};

  std::shuffle(allTargets.begin(), allTargets.end(),
               std::mt19937{std::random_device{}()});

  float cellSize = 60.0f;
  float offset = 20.0f;
  float panelWidth = 200.0f;
  unsigned int winW =
      (unsigned int)(offset * 2 + board.getWidth() * cellSize + panelWidth);
  unsigned int winH = (unsigned int)(offset * 2 + board.getHeight() * cellSize + 60);
  sf::RenderWindow window(sf::VideoMode({winW, winH}), "Ricochet Robots!");

  Screen currentScreen = Screen::MENU;

  int moveCount = 0;
  Color selectedColor = Color::Red;

  //butons colrs and posix
  float panelX = offset * 2 + board.getWidth() * cellSize;
  float btnW = 160.0f;
  float btnH = 50.0f;
  float btnSpacing = 10.0f;
  float btnsY = 200.0f;
  std::vector<Color> btnColors = {Color::Red, Color::Green, Color::Blue,
                                  Color::Yellow};
  std::vector<sf::Color> sfColors = {sf::Color::Red, sf::Color::Green,
                                     sf::Color::Blue, sf::Color::Yellow};

  bool showAISolution = false;
  std::vector<State> solution;
  int curSolutionState = 0;
  bool runAIAfterDraw = false;
  int targetN = 0;

  sf::Clock announceClock;
  bool showAnnounce = false;
  bool runAISolverBtn = false;
  bool runPhase2 = false;
  bool aiPhase2Pending = false;
  int aiCounterOffset = 0;
  bool showBestSolutionBanner = false;

  bool showHint = false;
  Color hintColor = Color::Red;
  int hintDx = 0, hintDy = 0;
  bool runHintBtn = false;

  bool showRatingBanner = false;
  bool pendingRating = false;
  std::string ratingText = "";
  int ratingPlayerMoves = 0;
  int ratingAIMoves = 0;

  while (window.isOpen()) {
    if (showAISolution) {
      if (curSolutionState < (int)solution.size()) {
        state = solution[curSolutionState];
        moveCount = aiCounterOffset + curSolutionState;
        curSolutionState++;
        sleep(1);
      } else if (aiPhase2Pending) {
        //phase 1 done
        sleep(1);
        aiPhase2Pending = false;
        showAISolution = false;
        state = initialState;
        moveCount = 0;
        runPhase2 = true;
      } else {
        //AI sol done
        showAISolution = false;
        if (pendingRating) {
          showRatingBanner = true;
          pendingRating = false;
        }
      }
    }
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto *mouseClick =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseClick->button == sf::Mouse::Button::Left) {
          float mx = (float)mouseClick->position.x;
          float my = (float)mouseClick->position.y;
          if (currentScreen != Screen::GAME) {
            Screen prev = currentScreen;
            currentScreen = handleMenuClick(currentScreen, mx, my, (float)winW,
                                            (float)winH);
            if (prev == Screen::MENU && currentScreen == Screen::GAME) {
              targetN = (int)(std::mt19937{std::random_device{}()}() %
                              allTargets.size());
              showAnnounce = true;
              announceClock.restart();
            }
          }
          for (int i = 0; i < 4; i++) {
            float by = btnsY + i * (btnH + btnSpacing);
            float bx = panelX + 20.0f;
            if (mx >= bx && mx <= bx + btnW && my >= by && my <= by + btnH)
              selectedColor = btnColors[i];
          }
          float bx = panelX + 20.0f;
          float by = btnsY + 50 + 4 * (btnH + btnSpacing);
          if (mx >= bx && mx <= bx + btnW && my >= by && my <= by + btnH) {
            board = Board(16, 16);
            std::shuffle(quadrants.begin(), quadrants.end(),
                         std::mt19937{std::random_device{}()});

            for (int i = 0; i < 4 && i < (int)quadrants.size(); i++) {
              board.placeQuadrant(rotateQuadrant(quadrants[i], rotations[i]),
                                  positions[i].first, positions[i].second);
            }
            redRobot.setPos({1, 1});
            greenRobot.setPos({14, 1});
            blueRobot.setPos({1, 14});
            yellowRobot.setPos({14, 14});

            state = State(board, redRobot, greenRobot, blueRobot, yellowRobot);
            initialState = state;

            validPositions.clear();
            for (auto wall : board.getWalls()) {
              if (((wall.pos.x == 7 || wall.pos.x == 8) &&
                   (wall.pos.y == 7 || wall.pos.y == 8)) ||
                  ((wall.pos.x == 1 || wall.pos.x == 14) &&
                   (wall.pos.y == 1 || wall.pos.y == 14))) {
                continue;
              }
              bool up = board.hasWall(wall.pos.x, wall.pos.y, 0, -1);
              bool down = board.hasWall(wall.pos.x, wall.pos.y, 0, 1);
              bool left = board.hasWall(wall.pos.x, wall.pos.y, -1, 0);
              bool right = board.hasWall(wall.pos.x, wall.pos.y, 1, 0);

              if ((up && left) || (up && right) || (down && left) ||
                  (down && right)) {
                validPositions.push_back(wall.pos);
              }
            }

            std::shuffle(validPositions.begin(), validPositions.end(),
                         std::mt19937{std::random_device{}()});

            allTargets = {{validPositions[0], Color::Red},
                          {validPositions[1], Color::Green},
                          {validPositions[2], Color::Blue},
                          {validPositions[3], Color::Yellow}};

            std::shuffle(allTargets.begin(), allTargets.end(),
                         std::mt19937{std::random_device{}()});

            moveCount = 0;
            selectedColor = Color::Red;
            showAISolution = false;
            solution.clear();
            curSolutionState = 0;
            runAIAfterDraw = false;
            showBestSolutionBanner = false;
            showRatingBanner = false;
            pendingRating = false;
            showHint = false;
            targetN = (int)(std::mt19937{std::random_device{}()}() %
                            allTargets.size());
            showAnnounce = true;
            announceClock.restart();
          }
          // AI solvr buttn
          float aiBtnY = btnsY + 50 + 4 * (btnH + btnSpacing) + btnH + 14.f +
                         20.f + 28.f + 12.f;
          if (mx >= panelX + 20.f && mx <= panelX + 20.f + btnW &&
              my >= aiBtnY && my <= aiBtnY + btnH) {
            runAISolverBtn = true;
          }
          // hint buttn
          float hintBtnY = aiBtnY + btnH + 10.f;
          if (mx >= panelX + 20.f && mx <= panelX + 20.f + btnW &&
              my >= hintBtnY && my <= hintBtnY + btnH) {
            runHintBtn = true;
          }
        }
      }

      if (currentScreen == Screen::GAME)
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          State prevState = state;
          if (keyPressed->code == sf::Keyboard::Key::Up)
            state = controller.moveRobot(state, selectedColor, Direction::UP);
          else if (keyPressed->code == sf::Keyboard::Key::Down)
            state = controller.moveRobot(state, selectedColor, Direction::DOWN);
          else if (keyPressed->code == sf::Keyboard::Key::Left)
            state = controller.moveRobot(state, selectedColor, Direction::LEFT);
          else if (keyPressed->code == sf::Keyboard::Key::Right)
            state =
                controller.moveRobot(state, selectedColor, Direction::RIGHT);

          if (!(state.getRobot(selectedColor).getPos() ==
                prevState.getRobot(selectedColor).getPos())) {
            moveCount++;
            showHint = false;

            if (state.checkWin(allTargets[targetN].color,
                               allTargets[targetN].pos)) {
              std::cout << "You reached the target in " << moveCount << " moves"
                        << std::endl;
              runAIAfterDraw = true;
            }
          }
        }
    }

    auto mousePos = sf::Mouse::getPosition(window);
    float mx = (float)mousePos.x, my = (float)mousePos.y;

    window.clear(sf::Color::Black);

    if (currentScreen == Screen::MENU) {
      drawMenuScreen(window, (float)winW, (float)winH, mx, my);
      window.display();
      continue;
    }
    if (currentScreen == Screen::CONTROLS) {
      drawControlsScreen(window, (float)winW, (float)winH, mx, my);
      window.display();
      continue;
    }
    if (currentScreen == Screen::HOW_TO_PLAY) {
      drawHowToPlayScreen(window, (float)winW, (float)winH, mx, my);
      window.display();
      continue;
    }

    // GAME
    state.getBoard().drawBoard(window);

    // Só mostrar o alvo actual
    {
      const auto &target = allTargets[targetN];
      sf::RectangleShape targetShape(sf::Vector2f(cellSize, cellSize));
      targetShape.setPosition(
          {offset + target.pos.x * cellSize, offset + target.pos.y * cellSize});
      if (target.color == Color::Red)
        targetShape.setFillColor(sf::Color(255, 0, 0, 180));
      else if (target.color == Color::Green)
        targetShape.setFillColor(sf::Color(0, 200, 0, 180));
      else if (target.color == Color::Blue)
        targetShape.setFillColor(sf::Color(0, 0, 255, 180));
      else if (target.color == Color::Yellow)
        targetShape.setFillColor(sf::Color(255, 220, 0, 180));
      window.draw(targetShape);
    }

    state.getRobot(Color::Red).draw(window, cellSize, offset);
    state.getRobot(Color::Green).draw(window, cellSize, offset);
    state.getRobot(Color::Blue).draw(window, cellSize, offset);
    state.getRobot(Color::Yellow).draw(window, cellSize, offset);

    //banner best sol
    if (showBestSolutionBanner) {
      float boardW = board.getWidth() * cellSize;
      float boardCx = offset + boardW / 2.f;
      float bannerY = offset + board.getHeight() * cellSize + 5.f;
      drawBestSolutionBanner(window, boardCx, bannerY, boardW);
    }

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

    // Botoes de selecao de robot
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

    float resetBtnY = btnsY + 50 + 4 * (btnH + btnSpacing);
    drawResetButton(window, panelX + 20.0f, resetBtnY, btnW, btnH,
                    mx >= panelX + 20.f && mx <= panelX + 20.f + btnW &&
                        my >= resetBtnY && my <= resetBtnY + btnH);

    //goal indic
    float indicatorY = resetBtnY + btnH + 14.f;
    drawTargetIndicator(window, allTargets[targetN].color, panelX + 20.f,
                        indicatorY, btnW);

    //ai solvr bttn
    float aiBtnY = indicatorY + 20.f + 28.f + 12.f;
    drawAIButton(window, panelX + 20.f, aiBtnY, btnW, btnH,
                 mx >= panelX + 20.f && mx <= panelX + 20.f + btnW &&
                     my >= aiBtnY && my <= aiBtnY + btnH);

    // hint buttn
    float hintBtnY = aiBtnY + btnH + 10.f;
    drawHintButton(window, panelX + 20.f, hintBtnY, btnW, btnH,
                   mx >= panelX + 20.f && mx <= panelX + 20.f + btnW &&
                       my >= hintBtnY && my <= hintBtnY + btnH);

    // seta de hint no tabuleiro
    if (showHint) {
      drawHintArrow(window, hintColor, state.getRobot(hintColor).getPos(),
                    hintDx, hintDy, cellSize, offset);
    }

    // rating banner da solucao do jogador
    if (showRatingBanner) {
      float boardCx = offset + board.getWidth() * cellSize / 2.f;
      float boardCy = offset + board.getHeight() * cellSize / 2.f;
      drawRatingBanner(window, ratingText, ratingPlayerMoves, ratingAIMoves, boardCx, boardCy);
    }

    // 5 sec thingy
    if (showAnnounce) {
      if (announceClock.getElapsedTime().asSeconds() < 5.f) {
        float boardCx = offset + board.getWidth() * cellSize / 2.f;
        float boardCy = offset + board.getHeight() * cellSize / 2.f;
        drawGameAnnounce(window, allTargets[targetN].color, boardCx, boardCy);
      } else {
        showAnnounce = false;
      }
    }

    window.display();

    if (runAIAfterDraw) {
     //won now showing best sol
      int savedPlayerMoves = moveCount;
      aiCounterOffset = 0;
      moveCount = 0;
      solution = aStar(initialState, allTargets[targetN]).path;
      int optimalMoves = (int)solution.size();
      solution.insert(solution.begin(), initialState);
      curSolutionState = 0;
      showAISolution = true;
      showBestSolutionBanner = true;
      showRatingBanner = false;
      runAIAfterDraw = false;

      // compara jogadas do player vs solucao otima
      int diff = savedPlayerMoves - optimalMoves;
      if (diff <= 0)      ratingText = "PERFEITO";
      else if (diff == 1) ratingText = "QUASE PERFEITO";
      else if (diff <= 3) ratingText = "MUITO BOM";
      else if (diff <= 6) ratingText = "BOM";
      else                ratingText = "VAI SER MELHOR NA PROXIMA";
      ratingPlayerMoves = savedPlayerMoves;
      ratingAIMoves = optimalMoves;
      pendingRating = true;
    }
    if (runAISolverBtn) {
      if (moveCount == 0) {
        //mostra a melhor solucao desde o inicio
        aiCounterOffset = 0;
        aiPhase2Pending = false;
        solution = aStar(initialState, allTargets[targetN]).path;
        solution.insert(solution.begin(), initialState);
        pendingRating = false;
        showRatingBanner = false;
      } else {
        // mostra melhor sol de onde esta
        aiCounterOffset = moveCount;
        aiPhase2Pending = true;
        solution = aStar(state, allTargets[targetN]).path;
        int aiRemainingMoves = (int)solution.size();
        solution.insert(solution.begin(), state);

        SolverResult optResult = aStar(initialState, allTargets[targetN]);
        int optimalMoves = (int)optResult.path.size();
        int totalMoves = moveCount + aiRemainingMoves;

        int diff = totalMoves - optimalMoves;
        if (diff <= 0)      ratingText = "PERFEITO";
        else if (diff == 1) ratingText = "QUASE PERFEITO";
        else if (diff <= 3) ratingText = "MUITO BOM";
        else if (diff <= 6) ratingText = "BOM";
        else                ratingText = "VAI SER MELHOR NA PROXIMA";
        ratingPlayerMoves = totalMoves;
        ratingAIMoves = optimalMoves;
        pendingRating = true;
        showRatingBanner = false;
      }
      curSolutionState = 0;
      showAISolution = true;
      showBestSolutionBanner = true;
      runAISolverBtn = false;
    }
    if (runPhase2) {
      // solucao melhor desde o starting point
      aiCounterOffset = 0;
      solution = aStar(initialState, allTargets[targetN]).path;
      solution.insert(solution.begin(), initialState);
      curSolutionState = 0;
      showAISolution = true;
      showBestSolutionBanner = true;
      runPhase2 = false;
    }
    if (runHintBtn) {
      runHintBtn = false;
      SolverResult hintResult = aStar(state, allTargets[targetN]);
      if (!hintResult.path.empty()) {
        State &nextState = hintResult.path[0];
        for (Color c : {Color::Red, Color::Green, Color::Blue, Color::Yellow}) {
          Position p0 = state.getRobot(c).getPos();
          Position p1 = nextState.getRobot(c).getPos();
          if (!(p0 == p1)) {
            hintColor = c;
            hintDx = p1.x - p0.x;
            hintDy = p1.y - p0.y;
            // normalizar para -1/0/1
            if (hintDx > 1)  hintDx = 1;
            if (hintDx < -1) hintDx = -1;
            if (hintDy > 1)  hintDy = 1;
            if (hintDy < -1) hintDy = -1;
            showHint = true;
            break;
          }
        }
      }
    }
  }

  return 0;
}
