#include "Solver.h"
#include <deque>
#include <set>
#include <vector>

std::vector<State> bfs(State initialState) {
  std::deque<std::vector<State>> queue;
  std::set<State> visited;
  std::vector<Color> colors = {Red, Green, Blue, Yellow};
  std::vector<Direction> directions = {Direction::LEFT, Direction::RIGHT,
                                       Direction::DOWN, Direction::UP};
  queue.push_back({initialState});
  visited.insert(initialState);
  Controller controller;

  while (!queue.empty()) {
    std::vector<State> path = queue.front();
    queue.pop_front();

    State node = path.back();
    for (int i = 0; i < 4; i++) {
      if (node.checkWin(colors[i], node.getRobot(colors[i]).getPos())) {
        return path;
      }
    }

    for (Color color : colors) {
      for (Direction direction : directions) {
        State newState = controller.moveRobot(node, color, direction);
        if (visited.find(newState) == visited.end()) {
          std::vector<State> new_path = path;
          new_path.push_back(newState);
          queue.push_back(new_path);
          visited.insert(newState);
        }
      }
    }
  }
}
