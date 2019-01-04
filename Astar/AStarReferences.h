#pragma once

#include <vector>

class Operation
{
public:
	float cost;

	Operation(float cost) :cost(cost) {}
	~Operation() {}
};

class State
{
public:
	State *parent;
	Operation *actionFromParent;
	double f, g, h;
	virtual int compareTo(State *state) = 0;

	State() {}
	~State() {}
};

class Goal
{
public:
	virtual bool isGoalSatisfied(State *state) = 0;

	Goal() {}
	~Goal() {}
};


class Heuristic
{
public:
	virtual double estimateCost(State *state) = 0;
	Heuristic(Goal *goal) : goal(goal) {}
	~Heuristic() {}
private:
	Goal *goal;
};

class World
{
public:
	virtual std::vector<Operation*> getActions(State *state) = 0;
	virtual State* execute(State *state, Operation *operation) = 0;

	World() {}
	~World() {}
};
