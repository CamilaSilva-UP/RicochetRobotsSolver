#include "Board.h"
#include "Controller.h"
#include "Quadrant.h"
#include "Quadrants.h"
#include "Robot.h"
#include "Solver.h"
#include "State.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <random>
#include <vector>

// Random boards
static State makeRandomState(std::mt19937 &rng) {
  Board board(16, 16);
  auto quadrants = getQuadrants();
  std::shuffle(quadrants.begin(), quadrants.end(), rng);

  std::vector<std::pair<int, int>> positions = {{0, 0}, {8, 0}, {8, 8}, {0, 8}};
  std::vector<int> rotations = {0, 90, 180, 270};
  for (int i = 0; i < 4; i++)
    board.placeQuadrant(rotateQuadrant(quadrants[i], rotations[i]),
                        positions[i].first, positions[i].second);

  Robot r, g, b, y;
  r.setPos({1, 1});   r.setColor(Color::Red);
  g.setPos({14, 1});  g.setColor(Color::Green);
  b.setPos({1, 14});  b.setColor(Color::Blue);
  y.setPos({14, 14}); y.setColor(Color::Yellow);

  return State(board, r, g, b, y);
}

// choses random targets
static std::vector<Target> getValidTargets(Board &board) {
  std::vector<Color> colors = {Color::Red, Color::Green, Color::Blue, Color::Yellow};
  std::vector<Target> targets;

  for (auto &wall : board.getWalls()) {
    int x = wall.pos.x, y = wall.pos.y;
    // excludes center and initial positions
    if ((x == 7 || x == 8) && (y == 7 || y == 8)) continue;
    if ((x == 1 || x == 14) && (y == 1 || y == 14)) continue;

    bool up    = board.hasWall(x, y, 0, -1);
    bool down  = board.hasWall(x, y, 0,  1);
    bool left  = board.hasWall(x, y, -1, 0);
    bool right = board.hasWall(x, y,  1, 0);

    if ((up && left) || (up && right) || (down && left) || (down && right)) {
      for (Color c : colors)
        targets.push_back({wall.pos, c});
    }
  }
  return targets;
}

int main() {
  const int NUM_BOARDS  = 20;
  const int TARGETS_PER_BOARD = 5;
  std::mt19937 rng(42); // semente fixa para reprodutibilidade

  printf("board,target,color,opt_moves,bfs_nodes,bfs_ms,astar_nodes,astar_ms\n");

  int boardId = 0;
  while (boardId < NUM_BOARDS) {
    State initialState = makeRandomState(rng);
    Board board = initialState.getBoard();

    auto allTargets = getValidTargets(board);
    if (allTargets.empty()) continue;

    std::shuffle(allTargets.begin(), allTargets.end(), rng);
    int count = std::min((int)allTargets.size(), TARGETS_PER_BOARD);

    for (int t = 0; t < count; t++) {
      Target target = allTargets[t];

      // --- BFS ---
      auto t0 = std::chrono::high_resolution_clock::now();
      SolverResult resBFS = bfs(initialState, target);
      auto t1 = std::chrono::high_resolution_clock::now();
      double msBFS = std::chrono::duration<double, std::milli>(t1 - t0).count();

      // --- A* ---
      auto t2 = std::chrono::high_resolution_clock::now();
      SolverResult resAStar = aStar(initialState, target);
      auto t3 = std::chrono::high_resolution_clock::now();
      double msAStar = std::chrono::duration<double, std::milli>(t3 - t2).count();

      int optMoves = resBFS.path.empty() ? -1 : (int)resBFS.path.size() - 1;

      const char *colorName = (target.color == Red)    ? "Red"
                            : (target.color == Green)  ? "Green"
                            : (target.color == Blue)   ? "Blue"
                                                       : "Yellow";

      printf("%d,%d,%s,%d,%d,%.3f,%d,%.3f\n",
             boardId, t,
             colorName,
             optMoves,
             resBFS.nodesExpanded,   msBFS,
             resAStar.nodesExpanded, msAStar);
    }
    boardId++;
  }

  return 0;
}
