#include <iostream>
#include "Board.h"

Board::Board (int width, int height) {
    this -> width = width;
    this -> height = height;
}

void Board::addWall (int x, int y, bool up, bool down, bool left, bool right) {
    Wall w;
    w.pos = {x, y};
    w.up = up;
    w.down = down;
    w.left = left;
    w.right = right;

    walls.push_back(w);
}

bool Board::isInside (int x, int y) const{ 
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

void Board::drawBoard() const{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bool hasWallHere = false;
            for (auto &w : walls) {
                if (w.pos.x == x && w.pos.y == y) {
                    hasWallHere = true;
                    break;
                }
            }
            if (hasWallHere)
                std::cout << "# ";
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
}