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
	/*float a = pow( -1 * line -> a + 1, 2);
	float c = pow(radius,2);
	float d = pow(line->c,2);
	printf("\na %f, b %f , d %f , radius² *c * a - d %f\n", a, c, d, radius*radius* c*a - d);
	float dis = pow(radius, 2)*c*a - d;

	printf("(%f,%f)\n", (line->a*line->c + sqrt(dis)) / a, (line->c + line->a*sqrt(dis)) / a);*/
	
	return false;
}
