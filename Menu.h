#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Utils.h"

enum class Screen { MENU, CONTROLS, HOW_TO_PLAY, GAME };

void drawMenuScreen     (sf::RenderWindow &window, float winW, float winH, float mx, float my);
void drawControlsScreen (sf::RenderWindow &window, float winW, float winH, float mx, float my);
void drawHowToPlayScreen(sf::RenderWindow &window, float winW, float winH, float mx, float my);

// 5sec anouncing thingy
void drawGameAnnounce(sf::RenderWindow &window, Color targetColor, float boardCx, float boardCy);

// alvo permanente
void drawTargetIndicator(sf::RenderWindow &window, Color targetColor, float x, float y, float w);

// AI solver (butao)
void drawAIButton(sf::RenderWindow &window, float x, float y, float w, float h, bool isHov);

// bannerzinho em baixo
void drawBestSolutionBanner(sf::RenderWindow &window, float boardCx, float bannerY, float boardW);

// botão reset com texto
void drawResetButton(sf::RenderWindow &window, float x, float y, float w, float h, bool isHov);

// botão hint
void drawHintButton(sf::RenderWindow &window, float x, float y, float w, float h, bool isHov);

// seta de hint no tabuleiro (dx/dy: -1, 0 ou 1)
void drawHintArrow(sf::RenderWindow &window, Color robotColor, Position robotPos, int dx, int dy, float cellSize, float offset);

Screen handleMenuClick(Screen current, float cx, float cy, float winW, float winH);

#endif
