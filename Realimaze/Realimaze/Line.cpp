#include "Line.h"
void Line::translate(Vector2D offset)
{
	start = start + offset;
	end = end + offset;
}

void Line::CalculateLine(void)
{
	if (start.y != end.y && start.x != end.x)
	{
		a = (start.y - end.y) / (start.x - end.x);
		b = start.y - a * start.x;
		c = b;
	}
	else if (start.y == end.y && start.x != end.x)
	{
		a = 0;
		b = start.y;
	}
	else if (start.y != end.y && start.x == end.x)
	{

	}
}
