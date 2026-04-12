#include "Menu.h"
#include <vector>
#include <string>
#include <cctype>


static const uint8_t *getGlyph(char uc) {
  if (uc == '-') {
    static const uint8_t dash[7] = {0x00,0x00,0x00,0x1F,0x00,0x00,0x00};
    return dash;
  }
  static const uint8_t D[10][7] = {
    {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E}, // 0
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E}, // 1
    {0x0E,0x11,0x01,0x06,0x08,0x10,0x1F}, // 2
    {0x0E,0x11,0x01,0x06,0x01,0x11,0x0E}, // 3
    {0x11,0x11,0x11,0x1F,0x01,0x01,0x01}, // 4
    {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E}, // 5
    {0x0E,0x10,0x10,0x1E,0x11,0x11,0x0E}, // 6
    {0x1F,0x01,0x02,0x04,0x04,0x04,0x04}, // 7
    {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E}, // 8
    {0x0E,0x11,0x11,0x0F,0x01,0x11,0x0E}, // 9
  };
  if (uc >= '0' && uc <= '9') return D[uc - '0'];
  static const uint8_t G[27][7] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // espaço
    {0x0E,0x11,0x11,0x1F,0x11,0x11,0x11}, // A
    {0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E}, // B
    {0x0E,0x11,0x10,0x10,0x10,0x11,0x0E}, // C
    {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E}, // D
    {0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F}, // E
    {0x1F,0x10,0x10,0x1E,0x10,0x10,0x10}, // F
    {0x0E,0x11,0x10,0x17,0x11,0x11,0x0E}, // G
    {0x11,0x11,0x11,0x1F,0x11,0x11,0x11}, // H
    {0x0E,0x04,0x04,0x04,0x04,0x04,0x0E}, // I
    {0x07,0x01,0x01,0x01,0x11,0x11,0x0E}, // J
    {0x11,0x12,0x14,0x18,0x14,0x12,0x11}, // K
    {0x10,0x10,0x10,0x10,0x10,0x10,0x1F}, // L
    {0x11,0x1B,0x15,0x11,0x11,0x11,0x11}, // M
    {0x11,0x19,0x15,0x13,0x11,0x11,0x11}, // N
    {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E}, // O
    {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10}, // P
    {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D}, // Q
    {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11}, // R
    {0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E}, // S
    {0x1F,0x04,0x04,0x04,0x04,0x04,0x04}, // T
    {0x11,0x11,0x11,0x11,0x11,0x11,0x0E}, // U
    {0x11,0x11,0x11,0x11,0x0A,0x0A,0x04}, // V
    {0x11,0x11,0x11,0x15,0x15,0x1B,0x11}, // W
    {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11}, // X
    {0x11,0x11,0x0A,0x04,0x04,0x04,0x04}, // Y
    {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F}, // Z
  };
  if (uc >= 'A' && uc <= 'Z') return G[1 + (uc - 'A')];
  return G[0];
}

static void drawPixelText(sf::RenderWindow &w, const std::string &text,
                          float x, float y, float ps, sf::Color color) {
  float cx = x;
  for (char ch : text) {
    const uint8_t *rows = getGlyph((char)toupper((unsigned char)ch));
    for (int r = 0; r < 7; r++)
      for (int c = 0; c < 5; c++)
        if (rows[r] & (1 << (4 - c))) {
          sf::RectangleShape px({ps - 1.f, ps - 1.f});
          px.setFillColor(color);
          px.setPosition({cx + c * ps, y + r * ps});
          w.draw(px);
        }
    cx += 6.f * ps;
  }
}

static void drawPixelTextCentered(sf::RenderWindow &w, const std::string &text,
                                   float cx, float cy, float ps, sf::Color color) {
  float tw = (float)(text.size() * 6 - 1) * ps;
  drawPixelText(w, text, cx - tw / 2.f, cy - 3.5f * ps, ps, color);
}

// geometria dos buttons

static constexpr float BTN_W = 300.f, BTN_H = 60.f, BTN_GAP = 16.f;
static constexpr float BACK_W = 200.f, BACK_H = 50.f;

static float btnX(float winW) { return winW / 2.f - BTN_W / 2.f; }
static float btn1Y(float winH) { return winH / 2.f - 1.5f * BTN_H - BTN_GAP; }
static float btn2Y(float winH) { return btn1Y(winH) + BTN_H + BTN_GAP; }
static float btn3Y(float winH) { return btn2Y(winH) + BTN_H + BTN_GAP; }
static float backX(float winW) { return winW / 2.f - BACK_W / 2.f; }
static float backY(float winH) { return winH - 80.f; }

static bool hov(float mx, float my, float x, float y, float w, float h) {
  return mx >= x && mx <= x + w && my >= y && my <= y + h;
}

static void drawBtn(sf::RenderWindow &w, const std::string &label,
                    float x, float y, float bw, float bh,
                    sf::Color color, bool isHov) {
  if (isHov) {
    sf::RectangleShape outline({bw + 6.f, bh + 6.f});
    outline.setPosition({x - 3.f, y - 3.f});
    outline.setFillColor(sf::Color::Black);
    w.draw(outline);
  }
  sf::RectangleShape btn({bw, bh});
  btn.setPosition({x, y});
  btn.setFillColor(color);
  w.draw(btn);
  drawPixelTextCentered(w, label, x + bw / 2.f, y + bh / 2.f, 4.f,
                        sf::Color::White);
}

//menu

void drawMenuScreen(sf::RenderWindow &window, float winW, float winH,
                    float mx, float my) {
  // Fundo igual ao jogo
  sf::RectangleShape bg({winW, winH});
  bg.setFillColor(sf::Color::White);
  window.draw(bg);

  float cx = winW / 2.f;

  float ry0 = winH / 2.f - 2.5f * BTN_H - 80.f;
  float r = 20.f;
  std::vector<sf::Color> robotColors = {
    sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};
  for (int i = 0; i < 4; i++) {
    sf::CircleShape circle(r);
    circle.setFillColor(robotColors[i]);
    circle.setPosition({cx - 4 * r - 10.f + i * (2 * r + 14.f), ry0});
    window.draw(circle);
  }

  sf::RectangleShape sep({BTN_W + 40.f, 4.f});
  sep.setFillColor(sf::Color(180, 180, 180));
  sep.setPosition({cx - (BTN_W + 40.f) / 2.f, ry0 + 2 * r + 20.f});
  window.draw(sep);

  float bx = btnX(winW);
  drawBtn(window, "JOGAR",      bx, btn1Y(winH), BTN_W, BTN_H,
          sf::Color::Red,    hov(mx, my, bx, btn1Y(winH), BTN_W, BTN_H));
  drawBtn(window, "CONTROLOS",  bx, btn2Y(winH), BTN_W, BTN_H,
          sf::Color::Blue,   hov(mx, my, bx, btn2Y(winH), BTN_W, BTN_H));
  drawBtn(window, "COMO JOGAR", bx, btn3Y(winH), BTN_W, BTN_H,
          sf::Color::Green,  hov(mx, my, bx, btn3Y(winH), BTN_W, BTN_H));
}

// controls

void drawControlsScreen(sf::RenderWindow &window, float winW, float winH,
                        float mx, float my) {
  sf::RectangleShape bg({winW, winH});
  bg.setFillColor(sf::Color::White);
  window.draw(bg);

  float cx = winW / 2.f;
  float startY = 120.f;
  float ps = 4.f; // pixel size para texto

  drawPixelTextCentered(window, "CONTROLOS", cx, startY, ps, sf::Color::Black);

  sf::RectangleShape sep({BTN_W + 40.f, 4.f});
  sep.setFillColor(sf::Color(180, 180, 180));
  sep.setPosition({cx - (BTN_W + 40.f) / 2.f, startY + 30.f});
  window.draw(sep);

  float ks = 50.f, kgap = 6.f;
  float kx = cx - ks * 1.5f - kgap;
  float ky = startY + 60.f;
  sf::Color keyColor(210, 210, 210);
  sf::Color keyBorder(100, 100, 100);

  struct Key { float dx, dy; std::string lbl; };
  std::vector<Key> keys = {
    {ks + kgap, 0,        "CIMA"},
    {0,         ks + kgap,"ESQ"},
    {ks + kgap, ks + kgap,"BAIXO"},
    {2*(ks+kgap), ks+kgap,"DIR"},
  };
  for (auto &k : keys) {
    sf::RectangleShape key({ks, ks});
    key.setPosition({kx + k.dx, ky + k.dy});
    key.setFillColor(keyColor);
    key.setOutlineThickness(3.f);
    key.setOutlineColor(keyBorder);
    window.draw(key);
    drawPixelTextCentered(window, k.lbl,
                          kx + k.dx + ks / 2.f, ky + k.dy + ks / 2.f,
                          2.f, sf::Color::Black);
  }

  float descX = kx + 3 * (ks + kgap) + 30.f;
  float descY = ky + 20.f;
  drawPixelText(window, "MOVER ROBOT", descX, descY,       3.f, sf::Color::Black);
  drawPixelText(window, "SELECIONADO", descX, descY + 30.f, 3.f, sf::Color::Black);

  float ry2 = ky + 2 * (ks + kgap) + 50.f;
  drawPixelText(window, "CLICAR NO BOTAO", kx, ry2, 3.f, sf::Color::Black);
  drawPixelText(window, "SELECIONA O ROBOT DA COR DO MESMO", kx, ry2 + 26.f, 3.f, sf::Color::Black);

  std::vector<sf::Color> rc = {sf::Color::Red, sf::Color::Green,
                                sf::Color::Blue, sf::Color::Yellow};
  for (int i = 0; i < 4; i++) {
    sf::RectangleShape rb({40.f, 40.f});
    rb.setPosition({kx + i * 50.f, ry2 + 58.f});
    rb.setFillColor(rc[i]);
    window.draw(rb);
  }

  // reset button
  float ry3 = ry2 + 115.f;
  drawPixelText(window, "BOTAO ROXO", kx, ry3, 3.f, sf::Color::Black);
  drawPixelText(window, "REINICIA JOGO", kx, ry3 + 26.f, 3.f, sf::Color::Black);
  sf::RectangleShape mb({100.f, 36.f});
  mb.setPosition({kx + 260.f, ry3});
  mb.setFillColor(sf::Color::Magenta);
  window.draw(mb);

  drawBtn(window, "VOLTAR", backX(winW), backY(winH), BACK_W, BACK_H,
          sf::Color(100, 100, 100),
          hov(mx, my, backX(winW), backY(winH), BACK_W, BACK_H));
}

// como jogar screen

void drawHowToPlayScreen(sf::RenderWindow &window, float winW, float winH,
                          float mx, float my) {
  sf::RectangleShape bg({winW, winH});
  bg.setFillColor(sf::Color::White);
  window.draw(bg);

  float cx = winW / 2.f;
  float ps = 4.f;

  drawPixelTextCentered(window, "COMO JOGAR", cx, 120.f, ps, sf::Color::Black);

  sf::RectangleShape sep({BTN_W + 40.f, 4.f});
  sep.setFillColor(sf::Color(180, 180, 180));
  sep.setPosition({cx - (BTN_W + 40.f) / 2.f, 150.f});
  window.draw(sep);

  struct Rule { std::string line1, line2; sf::Color dot; };
  std::vector<Rule> rules = {
    {"O OBJETIVO DO JOGO E MOVER ROBOT ATE AO ALVO DA SUA COR","",sf::Color::Red},
    {"ROBOT DESLIZA ATE BATER NUMA PAREDE OU NUM ROBOT",        "",    sf::Color::Blue},
    {"UTILIZE AS SETAS DO TECLADO PARA MOVER O ROBOT SELECIONADO",         "",     sf::Color::Green},
    {"AO CHEGAR AO ALVO A NOSSA IA MOSTRA A SOLUCAO OTIMA",              "", sf::Color::Yellow},
    {"TENTA USAR O MENOR NUMERO DE JOGADAS POSSIVEL",               "",        sf::Color(150,0,150)},
  };

  float tx = cx - 460.f, ry = 175.f;
  for (auto &rule : rules) {
    sf::CircleShape dot(8.f);
    dot.setFillColor(rule.dot);
    dot.setPosition({tx - 26.f, ry + 2.f});
    window.draw(dot);
    drawPixelText(window, rule.line1, tx, ry,        3.f, sf::Color::Black);
    drawPixelText(window, rule.line2, tx, ry + 22.f, 3.f, sf::Color(80,80,80));
    ry += 110.f;
  }

  drawBtn(window, "VOLTAR", backX(winW), backY(winH), BACK_W, BACK_H,
          sf::Color(100, 100, 100),
          hov(mx, my, backX(winW), backY(winH), BACK_W, BACK_H));
}


static sf::Color toSf(Color c) {
  switch (c) {
    case Color::Red:    return sf::Color::Red;
    case Color::Green:  return sf::Color::Green;
    case Color::Blue:   return sf::Color::Blue;
    case Color::Yellow: return sf::Color::Yellow;
  }
  return sf::Color::White;
}

static const char *colorName(Color c) {
  switch (c) {
    case Color::Red:    return "VERMELHO";
    case Color::Green:  return "VERDE";
    case Color::Blue:   return "AZUL";
    case Color::Yellow: return "AMARELO";
  }
  return "";
}

// anouncer do targe

void drawGameAnnounce(sf::RenderWindow &window, Color targetColor,
                      float boardCx, float boardCy) {
  float pw = 460.f, ph = 160.f;
  float px = boardCx - pw / 2.f, py = boardCy - ph / 2.f;

  sf::RectangleShape panel({pw, ph});
  panel.setPosition({px, py});
  panel.setFillColor(sf::Color(240, 240, 240));
  panel.setOutlineThickness(5.f);
  panel.setOutlineColor(sf::Color::Black);
  window.draw(panel);

  drawPixelText(window, "LEVAR O ROBOT", px + 20.f, py + 20.f, 4.f, sf::Color::Black);

  float cr = 26.f;
  sf::CircleShape circle(cr);
  circle.setFillColor(toSf(targetColor));
  circle.setPosition({px + 20.f, py + 70.f});
  window.draw(circle);

  drawPixelText(window, colorName(targetColor),
                px + 20.f + cr * 2.f + 12.f, py + 78.f,
                4.f, toSf(targetColor));

  drawPixelText(window, "AO ALVO", px + pw - 180.f, py + 78.f, 4.f, sf::Color::Black);
}

// alvo

void drawTargetIndicator(sf::RenderWindow &window, Color targetColor,
                         float x, float y, float w) {
  drawPixelText(window, "ALVO:", x, y, 3.f, sf::Color::Black);

  sf::RectangleShape bar({w, 28.f});
  bar.setPosition({x, y + 20.f});
  bar.setFillColor(toSf(targetColor));
  window.draw(bar);
}

// botaozinho do solver

void drawAIButton(sf::RenderWindow &window, float x, float y, float w, float h, bool isHov) {
  sf::Color color(210, 100, 20); // laranja
  if (isHov) {
    sf::RectangleShape outline({w + 6.f, h + 6.f});
    outline.setPosition({x - 3.f, y - 3.f});
    outline.setFillColor(sf::Color::Black);
    window.draw(outline);
    color = sf::Color(230, 130, 50);
  }
  sf::RectangleShape btn({w, h});
  btn.setPosition({x, y});
  btn.setFillColor(color);
  window.draw(btn);
  drawPixelText(window, "AI SOLVER", x + 8.f, y + h / 2.f - 10.f, 3.f, sf::Color::White);
}

// ─── Botão Reset ─────────────────────────────────────────────────────────────

void drawResetButton(sf::RenderWindow &window, float x, float y, float w, float h, bool isHov) {
  sf::Color color = sf::Color::Magenta;
  if (isHov) {
    sf::RectangleShape outline({w + 6.f, h + 6.f});
    outline.setPosition({x - 3.f, y - 3.f});
    outline.setFillColor(sf::Color::Black);
    window.draw(outline);
  }
  sf::RectangleShape btn({w, h});
  btn.setPosition({x, y});
  btn.setFillColor(color);
  window.draw(btn);
  drawPixelTextCentered(window, "RESET", x + w / 2.f, y + h / 2.f, 4.f, sf::Color::White);
}

// ─── Botão Hint ──────────────────────────────────────────────────────────────

void drawHintButton(sf::RenderWindow &window, float x, float y, float w, float h, bool isHov) {
  sf::Color color(0, 150, 150);
  if (isHov) {
    sf::RectangleShape outline({w + 6.f, h + 6.f});
    outline.setPosition({x - 3.f, y - 3.f});
    outline.setFillColor(sf::Color::Black);
    window.draw(outline);
    color = sf::Color(0, 180, 180);
  }
  sf::RectangleShape btn({w, h});
  btn.setPosition({x, y});
  btn.setFillColor(color);
  window.draw(btn);
  drawPixelTextCentered(window, "HINT", x + w / 2.f, y + h / 2.f, 4.f, sf::Color::White);
}

// ─── Seta de Hint no tabuleiro ───────────────────────────────────────────────

void drawHintArrow(sf::RenderWindow &window, Color robotColor, Position robotPos, int dx, int dy, float cellSize, float offset) {
  float cx = offset + robotPos.x * cellSize + cellSize / 2.f;
  float cy = offset + robotPos.y * cellSize + cellSize / 2.f;
  float r  = cellSize * 0.4f;

  sf::Color col;
  switch (robotColor) {
    case Color::Red:    col = sf::Color::Red;    break;
    case Color::Green:  col = sf::Color::Green;  break;
    case Color::Blue:   col = sf::Color::Blue;   break;
    case Color::Yellow: col = sf::Color::Yellow; break;
  }

  // anel de destaque em volta do robot
  sf::CircleShape ring(r + 6.f);
  ring.setFillColor(sf::Color::Transparent);
  ring.setOutlineThickness(5.f);
  ring.setOutlineColor(sf::Color(col.r, col.g, col.b, 220));
  ring.setPosition({cx - r - 6.f, cy - r - 6.f});
  window.draw(ring);

  // seta (triângulo) a apontar na direção
  float fdx = (float)dx, fdy = (float)dy;
  float baseDist = r + 6.f;
  float tipDist  = r + 32.f;
  float hw = 14.f;
  // perpendicular a (fdx, fdy) -> (-fdy, fdx)
  float px = -fdy, py = fdx;

  sf::ConvexShape arrow;
  arrow.setPointCount(3);
  arrow.setFillColor(col);
  arrow.setPoint(0, {cx + fdx * tipDist,             cy + fdy * tipDist});
  arrow.setPoint(1, {cx + fdx * baseDist + px * hw,  cy + fdy * baseDist + py * hw});
  arrow.setPoint(2, {cx + fdx * baseDist - px * hw,  cy + fdy * baseDist - py * hw});
  window.draw(arrow);
}

// best solution banner

void drawBestSolutionBanner(sf::RenderWindow &window, float boardCx, float bannerY, float boardW) {
  sf::RectangleShape bar({boardW, 50.f});
  bar.setPosition({boardCx - boardW / 2.f, bannerY});
  bar.setFillColor(sf::Color(20, 20, 20));
  window.draw(bar);

  drawPixelTextCentered(window, "BEST SOLUTION - AI", boardCx, bannerY + 25.f, 4.f, sf::Color(210, 100, 20));
}

// banner de rating

void drawRatingBanner(sf::RenderWindow &window, const std::string &rating,
                      int playerMoves, int aiMoves,
                      float boardCx, float boardCy) {
  //  overlay sobre o tabuleiro
  sf::RectangleShape overlay({1400.f, 1400.f});
  overlay.setPosition({boardCx - 700.f, boardCy - 700.f});
  overlay.setFillColor(sf::Color(0, 0, 0, 140));
  window.draw(overlay);

  float pw = 560.f, ph = 240.f;
  float px = boardCx - pw / 2.f, py = boardCy - ph / 2.f;

  sf::RectangleShape panel({pw, ph});
  panel.setPosition({px, py});
  panel.setFillColor(sf::Color(25, 25, 35));
  panel.setOutlineThickness(5.f);
  panel.setOutlineColor(sf::Color(210, 100, 20));
  window.draw(panel);

  // "A TUA SOLUCAO "
  std::string playerLine = "A TUA SOLUCAO - " + std::to_string(playerMoves);
  drawPixelTextCentered(window, playerLine, boardCx, py + 38.f, 3.f, sf::Color(200, 200, 200));

  // linha separadora laranja
  sf::RectangleShape sep({pw - 40.f, 3.f});
  sep.setFillColor(sf::Color(210, 100, 20));
  sep.setPosition({px + 20.f, py + 72.f});
  window.draw(sep);

  // "SOLUCAO DA AI "
  std::string aiLine = "SOLUCAO DA AI - " + std::to_string(aiMoves);
  drawPixelTextCentered(window, aiLine, boardCx, py + 100.f, 3.f, sf::Color(160, 160, 160));

  // cor consoante o rating
  sf::Color ratingColor;
  if (rating == "PERFEITO")            ratingColor = sf::Color(0, 220, 80);
  else if (rating == "QUASE PERFEITO") ratingColor = sf::Color(160, 230, 0);
  else if (rating == "MUITO BOM")      ratingColor = sf::Color(230, 220, 0);
  else if (rating == "BOM")            ratingColor = sf::Color(230, 140, 0);
  else                                 ratingColor = sf::Color(220, 60, 60);

  drawPixelTextCentered(window, rating, boardCx, py + 175.f, 3.f, ratingColor);
}

// click logic

Screen handleMenuClick(Screen current, float cx, float cy, float winW, float winH) {
  if (current == Screen::MENU) {
    float bx = btnX(winW);
    if (hov(cx, cy, bx, btn1Y(winH), BTN_W, BTN_H)) return Screen::GAME;
    if (hov(cx, cy, bx, btn2Y(winH), BTN_W, BTN_H)) return Screen::CONTROLS;
    if (hov(cx, cy, bx, btn3Y(winH), BTN_W, BTN_H)) return Screen::HOW_TO_PLAY;
  } else if (current == Screen::CONTROLS || current == Screen::HOW_TO_PLAY) {
    if (hov(cx, cy, backX(winW), backY(winH), BACK_W, BACK_H))
      return Screen::MENU;
  }
  return current;
}
