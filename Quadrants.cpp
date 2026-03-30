#include "Quadrants.h"

static Quadrant makeQ1() {
  Quadrant q;
  q.walls.push_back({{2, 1}, false, false, true, false});
  q.walls.push_back({{1, 2}, true, false, false, false});
  q.walls.push_back({{2, 4}, false, true, false, true});
  q.walls.push_back({{2, 7}, false, false, true, false});
  q.walls.push_back({{5, 6}, false, false, false, true});
  q.walls.push_back({{6, 6}, true, false, false, false});
  q.walls.push_back({{5, 2}, false, true, true, false});
  q.walls.push_back({{7, 0}, false, false, true, false});
  q.walls.push_back({{7, 7}, true, false, true, false});
  return q;
}

static Quadrant makeQ2() {
  Quadrant q;
  q.walls.push_back({{7, 7}, false, false, true, false});
  q.walls.push_back({{7, 6}, false, true, false, false});
  q.walls.push_back({{2, 6}, false, false, false, true});
  q.walls.push_back({{0, 3}, false, true, false, false});
  q.walls.push_back({{0, 1}, false, false, false, true});
  q.walls.push_back({{1, 1}, true, false, false, false});
  q.walls.push_back({{5, 0}, false, false, true, false});
  q.walls.push_back({{6, 3}, true, false, false, false});
  q.walls.push_back({{7, 3}, false, false, true, false});
  q.walls.push_back({{5, 5}, true, false, true, false});
  return q;
}

static Quadrant makeQ3() {
  Quadrant q;
  q.walls.push_back({{6, 7}, false, false, false, true});
  q.walls.push_back({{7, 7}, true, false, false, false});
  q.walls.push_back({{6, 6}, false, false, true, false});
  q.walls.push_back({{5, 5}, false, true, false, false});
  q.walls.push_back({{0, 2}, false, true, false, false});
  q.walls.push_back({{4, 2}, false, true, false, false});
  q.walls.push_back({{3, 3}, false, false, false, true});
  q.walls.push_back({{1, 4}, false, false, false, true});
  q.walls.push_back({{1, 5}, true, false, false, false});
  q.walls.push_back({{2, 0}, false, false, true, false});
  q.walls.push_back({{6, 1}, true, false, false, false});
  q.walls.push_back({{7, 1}, false, false, true, false});
  return q;
}

static Quadrant makeQ4() {
  Quadrant q;
  q.walls.push_back({{7, 7}, true, false, true, false});
  q.walls.push_back({{4, 7}, false, false, true, false});
  q.walls.push_back({{3, 7}, false, true, false, false});
  q.walls.push_back({{0, 6}, true, false, false, false});
  q.walls.push_back({{6, 5}, false, false, true, false});
  q.walls.push_back({{5, 4}, false, true, false, false});
  q.walls.push_back({{1, 2}, false, true, true, false});
  q.walls.push_back({{2, 1}, false, true, false, true});
  q.walls.push_back({{6, 0}, false, false, true, false});
  return q;
}

static Quadrant makeQ5() {
  Quadrant q;
  q.walls.push_back({{6, 7}, false, false, false, true});
  q.walls.push_back({{7, 7}, true, false, false, false});
  q.walls.push_back({{2, 6}, false, false, true, false});
  q.walls.push_back({{1, 5}, false, true, false, false});
  q.walls.push_back({{7, 5}, false, false, true, false});
  q.walls.push_back({{6, 5}, true, false, false, false});
  q.walls.push_back({{5, 3}, true, false, true, false});
  q.walls.push_back({{2, 2}, false, true, false, true});
  q.walls.push_back({{0, 1}, false, true, false, false});
  q.walls.push_back({{5, 0}, false, false, false, true});
  return q;
}

static Quadrant makeQ6() {
  Quadrant q;
  q.walls.push_back({{6, 7}, false, false, false, true});
  q.walls.push_back({{7, 7}, true, false, false, false});
  q.walls.push_back({{0, 6}, true, false, false, false});
  q.walls.push_back({{6, 6}, true, false, false, false});
  q.walls.push_back({{6, 5}, false, false, false, true});
  q.walls.push_back({{3, 4}, false, true, false, false});
  q.walls.push_back({{4, 4}, false, false, true, false});
  q.walls.push_back({{4, 3}, false, false, false, true});
  q.walls.push_back({{5, 2}, false, true, false, false});
  q.walls.push_back({{1, 2}, false, false, false, true});
  q.walls.push_back({{2, 2}, true, false, false, false});
  q.walls.push_back({{1, 0}, false, false, false, true});
  return q;
}

static Quadrant makeQ7() {
  Quadrant q;
  q.walls.push_back({{7, 7}, true, false, true, false});
  q.walls.push_back({{4, 7}, true, false, false, false});
  q.walls.push_back({{3, 6}, false, false, false, true});
  q.walls.push_back({{6, 5}, true, false, false, true});
  q.walls.push_back({{0, 6}, true, false, false, false});
  q.walls.push_back({{1, 2}, true, false, true, false});
  q.walls.push_back({{6, 1}, false, true, false, false});
  q.walls.push_back({{7, 1}, false, false, true, false});
  q.walls.push_back({{5, 0}, false, false, true, false});
  return q;
}

static Quadrant makeQ8() {
  Quadrant q;
  q.walls.push_back({{7, 7}, true, false, true, false});
  q.walls.push_back({{7, 5}, true, false, true, false});
  q.walls.push_back({{4, 7}, true, false, false, false});
  q.walls.push_back({{4, 6}, false, false, true, false});
  q.walls.push_back({{0, 6}, false, true, false, false});
  q.walls.push_back({{2, 4}, false, true, false, true});
  q.walls.push_back({{1, 1}, false, true, false, false});
  q.walls.push_back({{0, 1}, false, false, false, true});
  q.walls.push_back({{6, 2}, true, false, false, false});
  q.walls.push_back({{7, 2}, false, false, true, false});
  return q;
}

std::vector<Quadrant> getQuadrants() {
  return {
      makeQ1(),
      makeQ2(),
      makeQ3(),
      makeQ4(),
      makeQ5(),
      makeQ6(),
      makeQ7(),
      makeQ8(),
  };
}
