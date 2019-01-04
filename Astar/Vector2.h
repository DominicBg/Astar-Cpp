#pragma once

struct Vector2
{
public :
	int x, y;
	Vector2(int x, int y) : x(x), y(y) {}
	Vector2() :x(0), y(0) {}
	int ManhattanDistance(const Vector2 v1, const Vector2 v2);
};

Vector2 operator +(const Vector2 v1, const Vector2 v2)
{
	return Vector2(v1.x + v2.x,v1.y + v2.y);
}
Vector2 operator -(const Vector2 v1, const Vector2 v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}
bool operator ==(const Vector2 v1, const Vector2 v2)
{
		return v1.x == v2.x && v1.y == v2.y;
}
int ManhattanDistance(const Vector2 v1, const Vector2 v2)
{
	return abs(v1.x - v2.x) + abs(v1.y + v2.y);
}