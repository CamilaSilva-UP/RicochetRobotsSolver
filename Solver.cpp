#include "Solver.h"
#include <deque>
#include <omp.h>
#include <set>
#include <unistd.h>
#include <vector>

std::vector<State> bfs(State initialState, std::vector<Target> targets) {
  std::deque<std::vector<State>> queue;
  std::vector<State> visited;
  std::vector<Color> colors = {Red, Green, Blue, Yellow};
  std::vector<Direction> directions = {Direction::LEFT, Direction::RIGHT,
                                       Direction::DOWN, Direction::UP};
  queue.push_back({initialState});
  visited.push_back(initialState);
  Controller controller;

  while (!queue.empty()) {
    std::vector<State> path = queue.front();
    queue.pop_front();

    State node = path.back();
    // node.print();
    // printf("Path size: %zu\n", path.size());
    for (int i = 0; i < 4; i++) {
      if (node.checkWin(targets[i].color, targets[i].pos)) {
        return path;
      }
    }

#pragma omp parallel for collapse(2)
    for (Color color : colors) {
      for (Direction direction : directions) {
        State newState = controller.moveRobot(node, color, direction);
        bool skip = false;
        for (State s : visited) {
          if (s == newState) {
            skip = true;
            break;
          }
        }
        if (!skip) {
          std::vector<State> new_path = path;
          new_path.push_back(newState);
          queue.push_back(new_path);
          visited.push_back(newState);
        }
      }
    }
  }
}
