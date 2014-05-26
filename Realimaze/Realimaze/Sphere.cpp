#include "Sphere.h"
#include "Line.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

void Sphere::translate(Vector2D offset)
{
	position = position + offset;
}

/*
checks wether this sphere intersect another circle
*/
bool Sphere::intersectSphere(const Sphere * sphere) const
{
	float a, b, c;
	a = fabsf(position.x - sphere->position.x);
	b = fabsf(position.y - sphere->position.y);
	c = sqrt(pow(a, 2) + pow(b, 2));
	if (c < radius + sphere -> radius)
		return true;
	return false;
}

/*
checks wether this sphere intersect another line
*/
bool Sphere::intersectLine(const Line * line) const
{
	//y = ax+b
	//(x-c)� + (y-d)� = r�
	//(x - c)� + (mx + b - d)� = r�
	//m� + 1 != 0, x1,2 = +-(sqrt(-b� - 2 b c m + 2 b d - c� m� + 2 c d m - d� + m� r� + r�) - b m + c + d m) / (m� + 1)	
	bool intersect = false;
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
		//x1 = (sqrt(-1 * pow(b, 2) - 2 * b*c*m - pow(c, 2)*pow(m, 2) + 2 * c*d*m - pow(d, 2) + pow(m, 2)*pow(radius, 2) + pow(radius, 2)) - b*m + c + d + m) / (pow(m, 2) + 1);
		if (-1 * pow(b, 2) - 2 * b*c*m - pow(c, 2)*pow(m, 2) + 2 * c*d*m - pow(d, 2) + pow(m, 2)*pow(radius, 2) + pow(radius, 2) >= 0)
		{
			intersect = true;
			printf("ja kut \n");
		}
	case 2:
		if (position.y + radius >= line->b && position.y - radius <= line->b)
			intersect = true;
		break;
	case 3:
		if (position.x + radius >= line->b && position.x - radius <= line->b)
			intersect = true;
		break;
	case 4:
		
		break;
	}
	//printf("%d", intersect);
	return intersect;
}
