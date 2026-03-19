#include "Board.h"
#include <iostream>
#include <set>

int main() {
  Board board(5, 5);
  board.addWall(0, 0, false, true, false, true);
  board.addWall(2, 2, true, false, false, false);

  board.drawBoard();

  return 0;
}
