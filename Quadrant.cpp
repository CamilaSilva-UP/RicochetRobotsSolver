#include "Quadrant.h"

// Rotates each wall 90 degrees clockwise
// 90° CW:  (x,y) → (7-y, x),  up→right, right→down, down→left, left→up

static Wall rotateWall90(const Wall &w) {
  Wall r;
  r.pos = {7 - w.pos.y, w.pos.x};
  r.up    = w.left;
  r.right = w.up;
  r.down  = w.right;
  r.left  = w.down;
  return r;
}

Quadrant rotateQuadrant(const Quadrant &q, int degrees) {
  int steps = (degrees / 90) % 4;
  Quadrant result = q;
  for (int i = 0; i < steps; i++) {
    Quadrant tmp;
    for (const auto &w : result.walls)
      tmp.walls.push_back(rotateWall90(w));
    result = tmp;
  }
  return result;
}
