#include "Sphere.h"
#include "Line.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

void Sphere::translate(Vector2D offset)
{
	position = position + offset; // x and y of sphere
}

/*
checks whether this sphere intersect another circle
*/
bool Sphere::intersectSphere(const Sphere * sphere) const
{
	float a, b, c;
	a = fabsf(position.x - sphere->position.x);
	b = fabsf(position.y - sphere->position.y);
	c = sqrt(pow(a, 2) + pow(b, 2));
	if (c <= radius + sphere -> radius)
		return true;
	return false;
}

/*
checks whether this sphere intersect another line
*/
bool Sphere::intersectLine(const Line * line) const
{
	//y = ax+b
	//(x-c)² + (y-d)² = r²
	//(x - c)² + (mx + b - d)² = r²
	//m² + 1 != 0, x1,2 = +-(sqrt(-b² - 2 b c m + 2 b d - c² m² + 2 c d m - d² + m² r² + r²) - b m + c + d m) / (m² + 1)	
	//http://www.wolframalpha.com/input/?i=%28x%20-%20c%29^2%20%2b%20%28mx%20%2b%20b%20-%20d%29^2%20=%20r^2
	bool intersect = false;
	//0 -> default, 1 -> l:y=ax+b, 2 -> end.y == start.y, 3 -> end.x == start.x, 4 -> start == end
	switch (line->state)
	{
	case 0:
		
		break;
	case 1:
		float b, c, m, d, x1, x2;
		b = line->b;
		c = position.x;
		m = line->a;
		d = position.y;
		//x1 =  (sqrt(-1 * pow(b, 2) - 2 * b*c*m - pow(c, 2)*pow(m, 2) + 2 * c*d*m - pow(d, 2) + pow(m, 2)*pow(radius, 2) + pow(radius, 2)) - b*m + c + d + m) / (pow(m, 2) + 1);
		//x2 = (-sqrt(-1 * pow(b, 2) - 2 * b*c*m - pow(c, 2)*pow(m, 2) + 2 * c*d*m - pow(d, 2) + pow(m, 2)*pow(radius, 2) + pow(radius, 2)) - b*m + c + d + m) / (pow(m, 2) + 1); 
		float rootX;
		rootX = -1 * pow(b, 2) - 2 * b*c*m - pow(c, 2)*pow(m, 2) + 2 * c*d*m - pow(d, 2) + pow(m, 2)*pow(radius, 2) + pow(radius, 2);
		if (rootX >= 0)
		{
			x1 = (sqrt(rootX) - b*m + c + d + m) / (pow(m, 2) + 1);
			x2 = (-1 * sqrt(rootX) - b*m + c + d + m) / (pow(m, 2) + 1);
			if ((x1 > line->start.x && x1 < line->end.x) || (x2 > line->start.x && x2 < line->end.x))
				intersect = true;
			printf("zet hier een break point");
		}
		break;
	case 2:
		if (position.y + radius >= line->b && position.y - radius < line->b)
			intersect = true;
		break;
	case 3:
		if (position.x + radius >= line->b && position.x - radius < line->b)
			intersect = true;
		break;
	case 4:
		float a, f, e;
		a = fabsf(position.x - line->end.x);
		f = fabsf(position.y - line->end.y);
		e = sqrt(pow(a, 2) + pow(f, 2));
		if (e < radius)
			intersect = true;
		break;
	}
	return intersect;
}
