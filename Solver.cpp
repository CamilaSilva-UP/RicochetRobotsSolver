#include "Solver.h"
#include <algorithm>
#include <deque>
#include <queue>
#include <set>
#include <unistd.h>
#include <vector>

SolverResult bfs(State initialState, Target target) {
  std::deque<std::vector<State>> queue;
  std::set<State> visited;
  std::vector<Color> colors;
  switch (target.color) {
  case Red:
    colors = {Red, Green, Blue, Yellow};
    break;
  case Green:
    colors = {Green, Red, Yellow, Blue};
    break;
  case Blue:
    colors = {Blue, Red, Yellow, Green};
    break;
  case Yellow:
    colors = {Yellow, Blue, Green, Red};
    break;
  }
  std::vector<Direction> directions = {Direction::LEFT, Direction::RIGHT,
                                       Direction::DOWN, Direction::UP};
  queue.push_back({initialState});
  visited.insert(initialState);
  Controller controller;
  int nodesExpanded = 0;

  while (!queue.empty()) {
    std::vector<State> path = queue.front();
    queue.pop_front();
    nodesExpanded++;

    State node = path.back();
    if (node.checkWin(target.color, target.pos)) {
      return {path, nodesExpanded};
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
  return {{}, nodesExpanded};
}

SolverResult aStar(State initialState, Target target) {
  Controller controller;
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nodeQueue;
  std::set<State> visited;
  int nodesExpanded = 0;

  Node root = {initialState,
               {},
               0,
               estimative(initialState, target),
               estimative(initialState, target)};
  nodeQueue.push(root);
  visited.insert(initialState);

  while (!nodeQueue.empty()) {
    Node toExplore = nodeQueue.top();
    nodeQueue.pop();
    nodesExpanded++;

    for (int color = 0; color < 4; color++) {
      for (int direction = 0; direction < 4; direction++) {
        State childState = controller.moveRobot(toExplore.state, Color(color),
                                                Direction(direction));
        std::vector<State> newPath = toExplore.path;
        newPath.push_back(childState);

        int childCost = toExplore.currentCost + 1;
        int estimativeToGoal = estimative(childState, target);

        Node newNode = {childState, newPath, childCost, estimativeToGoal,
                        childCost + estimativeToGoal};
        if (childState.checkWin(target.color, target.pos))
          return {newPath, nodesExpanded};

        if (visited.count(childState) == 0) {
          nodeQueue.push(newNode);
          visited.insert(childState);
        }
      }
    }
  }

  return {{}, nodesExpanded};
}

int estimative(State state, Target target) {
  Position robotPos = state.getRobot(target.color).getPos();
  Position targetPos = target.pos;
  if (robotPos.x == targetPos.x && robotPos.y == targetPos.y)
    return 0;
  else if (robotPos.x == targetPos.x || robotPos.y == targetPos.y)
    return 1;
  else
    return 2;
}
