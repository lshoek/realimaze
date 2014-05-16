#ifndef CIRCLE
#define CIRCLE

#include "Shape.h"
#include "Line.h"
#include "Vector2D.h"

class Circle
{
public:
	Vector2D position, deltaDistance;
	float radius;
	bool intersect(Line * line);
	void translate(Vector2D offset);

	Circle(float x, float y, float r) : position(x, y), deltaDistance(0, 0)
	{
		this->radius = r;
	}
	~Circle()
	{

	}
};



#endif
