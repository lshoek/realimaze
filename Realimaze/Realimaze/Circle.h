#ifndef CIRCLE
#define CIRCLE

#include "Shape.h"
#include "Line.h"
#include "Vector2D.h"

class Circle
{
public:
	Vector2D position, distanceRolled;
	float radius;
	int state;//0 = in game, -1 = lost, 1 = won
	bool intersect(Line * line);
	void translate(Vector2D offset);
	bool intersectCircle(const Circle * circle) const;
	bool Circle::intersectLine(const Line * line) const;

	Circle(float x, float y, float r) : position(x, y), distanceRolled(0, 0)
	{
		this->radius = r;
		state = 0;
	}
	~Circle()
	{

	}
};



#endif
