#pragma once

#include "Shape.h"
#include "Line.h"
#include "Vector2D.h"

class Sphere
{
public:
	Vector2D position, distanceRolled;
	float radius;
	
	bool intersect(Line * line);
	void translate(Vector2D offset);
	void resetLocation();
	bool intersectSphere(const Sphere * sphere) const;
	bool Sphere::intersectLine(const Line * line) const;

	Sphere();
	Sphere(float x, float y, float r) : position(x, y), distanceRolled(0, 0)
	{
		this->radius = r;
	}
	~Sphere()
	{

	}
};
