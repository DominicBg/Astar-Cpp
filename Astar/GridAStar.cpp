#include "Vector2.h"
#include "AStar.h"
using namespace std;

class GridAStar : AStar
{
public :
	char **map;
	int width;
	int height;
	Vector2 goalPosition;

	GridAStar() {}
	char GetPosition(Vector2 position);
	char GetPosition(int x, int y);
	vector<Vector2> FindPath(Vector2 start, Vector2 end, char** map, char* collisions);
};

