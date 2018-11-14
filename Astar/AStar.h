#pragma once

#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map> 
#include <algorithm>
#include <queue>
#include <vector>
#include "pch.h"
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

	//vector<Operation*> generatePlan(World *world, State *initialState, Goal *goal, Heuristic *heuristic)
	//{
	//	//heuristic deja init
	//	priority_queue<State*> openQueue;
	//	map<State*, bool> openMap;
	//	map<State*, bool> close;

	//	State *currentState = initialState;
	//	openQueue.push(initialState);
	//	openMap[initialState] = true;

	//	while (openQueue.size() > 0)
	//	{
	//		//Remove next smallest
	//		currentState = openQueue.top();
	//		openQueue.pop();
	//		openMap.erase(currentState);

	//		close[currentState] = true;

	//		if (goal->isGoalSatisfied(currentState))
	//		{
	//			break;
	//		}

	//		vector<Operation*> nextOperations = world->getActions(currentState);
	//		vector<State*> nextStates = generateNextStates(world, currentState, nextOperations);

	//		visitNextStates(nextStates, nextOperations, close, currentState, openMap, heuristic, openQueue);

	//		nextOperations.clear();
	//		nextStates.clear();
	//	}

	//	//maybe kill stuff
	//	return getActionsFromParent(currentState);
	//}

	//void visitNextStates (vector<State *> &nextStates, std::vector<Operation *> &nextOperations, std::map<State *, bool> &close, State * currentState, std::map<State *, bool> &openMap, Heuristic * heuristic, std::priority_queue<State *> &openQueue)
	//{
	//	for (int i = 0; i < nextStates.size(); i++)
	//	{
	//		State * nextState = nextStates[i];
	//		Operation * nextOperation = nextOperations[i];

	//		//Not in close
	//		if (close.find(nextState) != close.end())
	//		{
	//			nextState->parent = currentState;

	//			if (openMap.find(nextState) != openMap.end())
	//			{
	//				recalculateState(currentState, nextOperation, heuristic, nextState);
	//			}
	//			else
	//			{
	//				calculateState(nextState, currentState, nextOperation, heuristic);
	//				openMap[nextState] = true;
	//				openQueue.push(nextState);
	//			}
	//		}
	//	}
	//}

	//void recalculateState(State * currentState, Operation * nextOperation, Heuristic * heuristic, State * nextState)
	//{
	//	double newg = currentState->g + nextOperation->cost;
	//	double newf = newg + heuristic->estimateCost(nextState);
	//	if (newf < nextState->f)
	//	{
	//		nextState->g = newg;
	//		nextState->f = newf;
	//		//update heap
	//	}
	//}

	//void calculateState(State * nextState, State * currentState, Operation * nextOperation, Heuristic * heuristic)
	//{
	//	nextState->g = currentState->g + nextOperation->cost;
	//	nextState->f = nextState->g + heuristic->estimateCost(nextState);
	//}

	//vector<State*> generateNextStates(World *world, State* state, vector<Operation*>operations)
	//{
	//	vector<State*> nextStates;
	//	for (Operation *operation : operations)
	//	{
	//		State *nextState = world->execute(state, operation);
	//		nextState->actionFromParent = operation;
	//		nextState->parent = state;
	//		nextStates.push_back(nextState);
	//	}
	//	return nextStates;
	//}

	//vector<Operation*> getActionsFromParent(State *state)
	//{
	//	State * currentState = state;
	//	vector<Operation *> operations;
	//	while (currentState->parent != nullptr)
	//	{
	//		operations.push_back(currentState->actionFromParent);
	//		currentState = currentState->parent;
	//	}

	//	reverse(operations.begin(), operations.end());
	//	return operations;
	//}

};

//vector<Operation*> AStar::generatePlan(World *world, State *initialState, Goal *goal, Heuristic *heuristic)
//{
//	//heuristic deja init
//	priority_queue<State*> openQueue;
//	map<State*, bool> openMap;
//	map<State*, bool> close;
//
//	State *currentState = initialState;
//	openQueue.push(initialState);
//	openMap[initialState] = true;
//
//	while (openQueue.size() > 0)
//	{
//		//Remove next smallest
//		currentState = openQueue.top();
//		openQueue.pop();
//		openMap.erase(currentState);
//
//		close[currentState] = true;
//
//		if (goal->isGoalSatisfied(currentState))
//		{
//			break;
//		}
//
//		vector<Operation*> nextOperations = world->getActions(currentState);
//		vector<State*> nextStates = generateNextStates(world, currentState, nextOperations);
//
//		visitNextStates(nextStates, nextOperations, close, currentState, openMap, heuristic, openQueue);
//
//		nextOperations.clear();
//		nextStates.clear();
//	}
//
//	//maybe kill stuff
//	return getActionsFromParent(currentState);
//}
//
//void AStar::visitNextStates(vector<State *> &nextStates, std::vector<Operation *> &nextOperations, std::map<State *, bool> &close, State * currentState, std::map<State *, bool> &openMap, Heuristic * heuristic, std::priority_queue<State *> &openQueue)
//{
//	for (int i = 0; i < nextStates.size(); i++)
//	{
//		State * nextState = nextStates[i];
//		Operation * nextOperation = nextOperations[i];
//
//		//Not in close
//		if (close.find(nextState) != close.end())
//		{
//			nextState->parent = currentState;
//
//			if (openMap.find(nextState) != openMap.end())
//			{
//				recalculateState(currentState, nextOperation, heuristic, nextState);
//			}
//			else
//			{
//				calculateState(nextState, currentState, nextOperation, heuristic);
//				openMap[nextState] = true;
//				openQueue.push(nextState);
//			}
//		}
//	}
//}
//
//void AStar::recalculateState(State * currentState, Operation * nextOperation, Heuristic * heuristic, State * nextState)
//{
//	double newg = currentState->g + nextOperation->cost;
//	double newf = newg + heuristic->estimateCost(nextState);
//	if (newf < nextState->f)
//	{
//		nextState->g = newg;
//		nextState->f = newf;
//		//update heap
//	}
//}
//
//void AStar::calculateState(State * nextState, State * currentState, Operation * nextOperation, Heuristic * heuristic)
//{
//	nextState->g = currentState->g + nextOperation->cost;
//	nextState->f = nextState->g + heuristic->estimateCost(nextState);
//}
//
//vector<State*> AStar::generateNextStates(World *world, State* state, vector<Operation*>operations)
//{
//	vector<State*> nextStates;
//	for (Operation *operation : operations)
//	{
//		State *nextState = world->execute(state, operation);
//		nextState->actionFromParent = operation;
//		nextState->parent = state;
//		nextStates.push_back(nextState);
//	}
//	return nextStates;
//}
//
//vector<Operation*> AStar::getActionsFromParent(State *state)
//{
//	State * currentState = state;
//	vector<Operation *> operations;
//	while (currentState->parent != nullptr)
//	{
//		operations.push_back(currentState->actionFromParent);
//		currentState = currentState->parent;
//	}
//
//	reverse(operations.begin(), operations.end());
//	return operations;
//}

#endif