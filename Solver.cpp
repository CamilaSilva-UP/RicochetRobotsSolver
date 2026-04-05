#include "Solver.h"
#include <deque>
#include <set>
#include <unistd.h>
#include <vector>

std::vector<State> bfs(State initialState, std::vector<Target> targets) {
  std::deque<std::vector<State>> queue;
  // std::set<State> visited;
  std::vector<Color> colors = {Red, Green, Blue, Yellow};
  std::vector<Direction> directions = {Direction::LEFT, Direction::RIGHT,
                                       Direction::DOWN, Direction::UP};
  queue.push_back({initialState});
  // visited.insert(initialState);
  Controller controller;

  for (auto target : targets) {
    std::cout << target.color << target.pos.x << target.pos.y << std::endl;
  }

  while (!queue.empty()) {
    std::vector<State> path = queue.front();
    queue.pop_front();

    State node = path.back();
    node.print();
    printf("Path size: %zu\n", path.size());
    for (int i = 0; i < 4; i++) {
      if (node.checkWin(targets[i].color, targets[i].pos)) {
        return path;
      }
    }

    for (Color color : colors) {
      for (Direction direction : directions) {
        State newState = controller.moveRobot(node, color, direction);
        // TODO: check visited to not repeat paths
        std::vector<State> new_path = path;
        new_path.push_back(newState);
        queue.push_back(new_path);
        // visited.insert(newState);
      }
    }
  }
}
