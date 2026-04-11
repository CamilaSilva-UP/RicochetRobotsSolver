#include "Solver.h"
#include <algorithm>
#include <deque>
#include <queue>
#include <unistd.h>
#include <vector>
#include <set>

std::vector<State> bfs(State initialState, Target target) {
  std::deque<std::vector<State>> queue;
  std::vector<State> visited;
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
  visited.push_back(initialState);
  Controller controller;

  while (!queue.empty()) {
    std::vector<State> path = queue.front();
    queue.pop_front();

    State node = path.back();
    // node.print();
    // printf("Path size: %zu\n", path.size());
    if (node.checkWin(target.color, target.pos)) {
      return path;
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

bool operator>(Node const &n1, Node const &n2) { return n1.f > n2.f; }

void printNode(Node node) {
  node.state.print();
  printf("%d\n", node.currentCost);
  printf("%d\n", node.estimateToGoal);
}

std::vector<State> aStar(State initialState, Target target) {
  Controller controller;
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> nodeQueue;
  std::set<State> visited;

  Node root = {initialState, {}, 0, estimative(initialState, target),
               estimative(initialState, target)};
  nodeQueue.push(root);
  visited.insert(initialState);

  while (!nodeQueue.empty()) {
    Node toExplore = nodeQueue.top();
    nodeQueue.pop();
    printNode(toExplore);

    for (int color = 0; color < 4; color++) {
      for (int direction = 0; direction < 4; direction++) {
        State childState = controller.moveRobot(toExplore.state, Color(color),
                                                Direction(direction));
        std::vector<State> newPath = toExplore.path;
        newPath.push_back(childState);

        int childCost = toExplore.currentCost + 1;
        int estimativeToGoal = estimative(childState, target);

        Node newNode = {childState, newPath, childCost, estimativeToGoal, childCost + estimativeToGoal};
        if (childState.checkWin(target.color, target.pos))
          return newPath;
        bool skip = false;
        if (visited.count(childState) == 0) { 
            nodeQueue.push(newNode);
            visited.insert(childState);
        }
      }
    }
  }

  return {};
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

