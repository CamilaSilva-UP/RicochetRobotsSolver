#ifndef Solver_H
#define Solver_H

#include "Controller.h"
#include "State.h"
#include "Utils.h"

std::vector<State> bfs(State initialState, Target target);

struct Node {
  State *state;
  Node *parent;
  int currentCost;
  int estimateToGoal;
  int f;
};

std::vector<State> aStar(State initialState, Target target);
int estimative(State state, Target target);
std::vector<State> rebuildPath(Node leaf);

#endif
