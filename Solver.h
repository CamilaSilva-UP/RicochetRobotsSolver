#ifndef Solver_H
#define Solver_H

#include "Controller.h"
#include "State.h"
#include "Utils.h"

std::vector<State> bfs(State initialState, std::vector<Target> targets);

#endif
