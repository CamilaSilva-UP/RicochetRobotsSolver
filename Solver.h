#ifndef Solver_H
#define Solver_H

#include "Controller.h"
#include "State.h"
#include "Utils.h"

struct SolverResult {
  std::vector<State> path;
  int nodesExpanded;
};

SolverResult bfs(State initialState, Target target);

struct Node {
  State state;
  std::vector<State> path;
  int currentCost;
  int estimateToGoal;
  int f;
  bool operator>(const Node &other) const { return f > other.f; }
};

SolverResult aStar(State initialState, Target target);
int estimative(State state, Target target);

#endif
