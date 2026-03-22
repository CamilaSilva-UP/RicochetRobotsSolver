#ifndef QUADRANT_H
#define QUADRANT_H

#include "Utils.h"
#include <vector>

// Um quadrante 8x8 com paredes em posições relativas (0-7, 0-7)
struct Quadrant {
  std::vector<Wall> walls;
};

// Roda um quadrante: 0, 90, 180 ou 270 graus (sentido horário)
Quadrant rotateQuadrant(const Quadrant &q, int degrees);

#endif
