#ifndef CIRCLE
#define CIRCLE

#include "Shape.h"
#include "Line.h"
#include "Vector2D.h"

class Circle : public Shape
{
public:
	Vector2D position;
	float radius;
	bool intersect(Line * line);
	void translate(Vector2D offset);
	Circle();
	~Circle();
};


void Circle::translate(Vector2D offset)
{

}
#endif
