#include "Solver.h"
#include <deque>
#include <set>

void bfs(State initialState) {
  std::deque<State> queue;
  std::set<State> visited;
  std::vector<State> traversalOrder;
  std::vector<Color> colors = {Red, Green, Blue, Yellow};
  std::vector<Direction> directions = {Direction::LEFT, Direction::RIGHT,
                                       Direction::DOWN, Direction::UP};
  queue.push_back(initialState);
  visited.insert(initialState);
  Controller controller;

  while (!queue.empty()) {
    State current = queue.front();
    queue.pop_front();
    traversalOrder.push_back(current);

    // TODO: If winning condition, return result

    for (Color color : colors) {
      for (Direction direction : directions) {
        State newState = controller.moveRobot(current, color, direction);
        if (visited.find(newState) != visited.end()) {
          queue.push_back(newState);
          visited.insert(newState);
        }
      }
    }
  }
}
