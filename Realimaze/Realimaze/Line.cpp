#include "Line.h"
void Line::translate(Vector2D offset)
{
	start = start + offset;
	end = end + offset;
}