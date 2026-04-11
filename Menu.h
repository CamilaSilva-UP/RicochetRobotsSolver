#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Utils.h"

enum class Screen { MENU, CONTROLS, HOW_TO_PLAY, GAME };

void drawMenuScreen     (sf::RenderWindow &window, float winW, float winH, float mx, float my);
void drawControlsScreen (sf::RenderWindow &window, float winW, float winH, float mx, float my);
void drawHowToPlayScreen(sf::RenderWindow &window, float winW, float winH, float mx, float my);

// Anúncio de 5 segundos no centro do tabuleiro
void drawGameAnnounce(sf::RenderWindow &window, Color targetColor, float boardCx, float boardCy);

// Indicador permanente da cor alvo no painel lateral
void drawTargetIndicator(sf::RenderWindow &window, Color targetColor, float x, float y, float w);

// Botão AI Solver no painel lateral
void drawAIButton(sf::RenderWindow &window, float x, float y, float w, float h, bool isHov);

Screen handleMenuClick(Screen current, float cx, float cy, float winW, float winH);

#endif
