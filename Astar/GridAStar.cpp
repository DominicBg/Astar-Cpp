#include "Vector2.h"
#include "AStar.h"
using namespace std;

//mettre en .h
class GridAStar : AStar
{
public :
	char **map;
	int width;
	int height;
	Vector2 goalPosition;

	GridAStar() {}
	char GetPosition(Vector2 position)
	{
		return GetPosition(position.x, position.y);
	}
	char GetPosition(int x, int y)
	{ 
		return map[x][y];
	}
	vector<Vector2> FindPath(Vector2 _start, Vector2 _end, char** _map, int _width, int _height, vector<char> collisions);
};

vector<Vector2> GridAStar::FindPath(Vector2 start, Vector2 end, char** _map, int _width, int _height, vector<char> collisions)
{
	map = _map;
	width = _width;
	height = _height;

	GridWorld* world = new GridWorld(map, collisions, this);
	GridState* initialState = new GridState(start, this);
	// Console.WriteLine(initialState.ToString());

	GridGoal* goal = new GridGoal(end);
	goalPosition = end;
	GridHeuristic* heuristic = new GridHeuristic(goal);

	vector<Operation> operations = AStarGenerator.GeneratePlan(world, initialState, goal, heuristic);
	//Si pas de chemin
	//if (operations == nullptr)
	//	return nullptr;

	//Convertis les chemins en vector2
	vector<Vector2> directions = new vector<Vector2>();
	for (int i = 0; i < operations.size(); i++)
	{
		GridOperation gridOperation = (GridOperation*)operations[i];
		directions.push_back(gridOperation.direction);
	}
	return directions;
	
}

class GridWorld : public World
{
	char** map;
	vector<char> collisions;
	GridAStar* gridAStar;

	Vector2 directions[] =
	{
		Vector2(1,0),
		Vector2(0,1),
		Vector2(-1,0),
		Vector2(0,-1),
	};

	public : 
		GridWorld(char** map, char* collisions, GridAStar* gridAStar) : map(map), collisions(collisions), gridAStar(gridAStar){}
		State* Executer(State* state, Operation* a);
		vector<Operation> GetActions(State* state);
		bool HasCollision(Vector2 position);
		bool InBound(Vector2 position);

};

State* GridWorld::Executer(State* state, Operation* a)
{
	GridState* gridState = (GridState*)state;
	GridOperation* gridAction = (GridOperation*)a;

	return new GridState(gridState->position + gridAction->direction, gridAStar);
}

//Genere les direction possibles pour aller au autres place
vector<Operation> GridWorld::GetActions(State* state)
{
	GridState* gridState = (GridState*)state;
	vector<Operation> operations = new vector<Operation>();
	for (int i = 0; i < 4; i++)
	{
		Vector2 newPosition = gridState->position + directions[i];
		if (InBound(newPosition) && !HasCollision(newPosition))
		{
			operations.push_back(new GridOperation(directions[i]));
		}
	}
	return operations;
}

bool GridWorld::HasCollision(Vector2 position)
{
	char currentCollision = gridAStar->GetPosition(position);
	for (int i = 0; i < collisions.size(); i++)
	{
		if (currentCollision == collisions[i])
			return true;
	}
	return false;
}

bool GridWorld::InBound(Vector2 position)
{
	return position.x >= 0 && position.y >= 0 && position.x < gridAStar->width && position.y < gridAStar->heigth;
}



class GridOperation : Operation
{
	public :
		Vector2 direction;
		GridOperation(Vector2 direction) : direction(direction) {}

	string ToString()
	{
		return direction.ToString();
	}
};

//

class GridState: State
{
public:
	Vector2 position;
	GridAStar* gridAStar;

	 GridState(Vector2 position, GridAStar gridAStar) : position(position), gridAStar(gridAStar) {}
	 int CompareTo(State* other);
	 //bool Equals(object obj); //override?
	 int GetHashCode();
	 string ToString();
};


int GridState::CompareTo(State* other)
{
	GridState* otherState = (GridState*)other;
	if (f == other.f && position == otherState.position)
		return 0;
	else if (f > other.f)
		return 1;
	else
		return -1;
}

//oh boy
bool GridState::Equals(object obj)
{
	var state = obj as GridState;
	return state != null && (position == state.position);
}
//oh boy
int GridState::GetHashCode()
{
	return 1206833562 + EqualityComparer<Vector2>.Default.GetHashCode(position);
}

string GridState::ToString()
{
	string stringMap = "";

	//width or height
	for (int i = 0; i < gridAStar->height; i++)
	{
		//width or height
		for (int j = 0; j < gridAStar->width; j++)
		{
			if (j == position.x && i == position.y)
				stringMap += "X";
			else
				stringMap += gridAStar->map[i, j];

		}
		stringMap += "\n";
	}
	
	return stringMap;
}


//
class GridHeuristic : Heuristic
{
	GridGoal* gridGoal;

	public:
		GridHeuristic(GridGoal* gridGoal) : gridGoal(gridGoal) {}


	double EstimateCost(State* state)
	{
		GridState* gridState = (GridState*)state;
		return ManhattanDistance(gridState->position, gridGoal->endPosition);
	}
};

class GridGoal : Goal
{
	public:
	
		Vector2 endPosition;
		GridGoal(Vector2 endPosition) : endPosition(endPosition) {}

		bool GoalSatisfied(State* state)
		{
			GridState* gridState = (GridState*)state;
			return gridState->position == endPosition;
		}
};