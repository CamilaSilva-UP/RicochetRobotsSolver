#include "Board.h"

Board::Board(int width, int height) {
  this->width = width;
  this->height = height;
}

Board::Board() {
  this->width = 16;
  this->height = 16;
}

void Board::addWall(int x, int y, bool up, bool down, bool left, bool right) {
  Wall w;
  w.pos = {x, y};
  w.up = up;
  w.down = down;
  w.left = left;
  w.right = right;

  walls.push_back(w);
}

bool Board::isInside(int x, int y) const {
  return x >= 0 && x < width && y >= 0 && y < height;
}

bool Board::hasWall(int x, int y, int dx, int dy) const{
  for (auto &w : walls) {
    if (w.pos.x == x && w.pos.y == y) {
      if (dx == -1 && w.left) return true;
      if (dx == 1 && w.right) return true;
      if (dy == 1 && w.down) return true;
      if (dy == -1 && w.up) return  true;
    }
  }
  return false;
}

void Board::drawBoard(sf::RenderWindow &window) const {
  float cellSize = 60.0f;
  float offset = 20.0f;

  // 1. Desenhar as células (grelha de fundo)
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
      cell.setPosition({offset + x * cellSize, offset + y * cellSize});
      cell.setFillColor(sf::Color(220, 220, 220)); // Cinzento claro
      cell.setOutlineThickness(1.0f);
      cell.setOutlineColor(sf::Color(180, 180, 180)); // Linhas da grelha
      window.draw(cell);
    }
  }

  // 2. Desenhar as paredes do Ricochet Robots
  float wallThickness = 6.0f; // Grossura da parede

  for (const auto &w : walls) {
    float px = offset + w.pos.x * cellSize;
    float py = offset + w.pos.y * cellSize;

    sf::RectangleShape wallShape;
    wallShape.setFillColor(sf::Color::Black); // Cor da parede

    if (w.up) {
      wallShape.setSize(sf::Vector2f(cellSize, wallThickness));
      wallShape.setPosition({px, py - wallThickness / 2});
      window.draw(wallShape);
    }
    if (w.down) {
      wallShape.setSize(sf::Vector2f(cellSize, wallThickness));
      wallShape.setPosition({px, py + cellSize - wallThickness / 2});
      window.draw(wallShape);
    }
    if (w.left) {
      wallShape.setSize(sf::Vector2f(wallThickness, cellSize));
      wallShape.setPosition({px - wallThickness / 2, py});
      window.draw(wallShape);
    }
    if (w.right) {
      wallShape.setSize(sf::Vector2f(wallThickness, cellSize));
      wallShape.setPosition({px + cellSize - wallThickness / 2, py});
      window.draw(wallShape);
    }
  }
}

std::vector<Wall> Board::getWalls() { return this->walls; }

void Board::placeQuadrant(const Quadrant &q, int offsetX, int offsetY) {
  for (const auto &w : q.walls) {
    addWall(w.pos.x + offsetX, w.pos.y + offsetY, w.up, w.down, w.left, w.right);
  }
}

int Board::getWidth() const { return this->width; }
int Board::getHeight() const { return this->height; }
