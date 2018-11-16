#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map> 
#include <algorithm>
#include <queue>
#include <vector>

//#include "stdafx.h"
#include "AStarReferences.h"

class AStar
{
public:
	vector<Operation*> generatePlan(World *world, State *initialState, Goal *goal, Heuristic *heuristic);
	AStar() {}
	~AStar() {}
private:
	void visitNextStates(vector<State *> &nextStates, std::vector<Operation *> &nextOperations, std::map<State *, bool> &close, State * currentState, std::map<State *, bool> &openMap, Heuristic * heuristic, std::priority_queue<State *> &openQueue);
	void recalculateState(State * currentState, Operation * nextOperation, Heuristic * heuristic, State * nextState);
	void calculateState(State * nextState, State * currentState, Operation * nextOperation, Heuristic * heuristic);
	vector<State*> generateNextStates(World*, State*, vector<Operation*>);
	vector<Operation*> getActionsFromParent(State *state);
};
