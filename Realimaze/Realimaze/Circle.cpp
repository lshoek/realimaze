#include "Circle.h"
#include "Line.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

void Circle::translate(Vector2D offset)
{
	position = position + offset;
}

bool Circle::intersectCircle(const Circle * circle) const
{
	
	return true;
}

bool Circle::intersectLine(const Line * line) const
{
	//y = ax+b
	//(x-c)² + (y-d)² = r²

	float a = -1 * line->a;
	float b = 1;
	float c = line->b;
	float r = radius;

	float D = pow(r,2)*
		(pow(a,2) + pow(b,2)) 
		- pow(c,2);
	printf("D voor de wortel%f\n", D);
	
	return false;
}
