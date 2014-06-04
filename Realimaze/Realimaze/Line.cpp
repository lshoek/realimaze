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
		state = 1;
	}
	else if (start.y == end.y && start.x != end.x)
	{
		a = 0;
		b = start.y;
		state = 2;
	}
	else if (start.y != end.y && start.x == end.x)
	{
		state = 3;
		b = start.x;
	}
	else if (start.y == end.y && start.x == end.x)
	{
		state = 4;
	}
}
