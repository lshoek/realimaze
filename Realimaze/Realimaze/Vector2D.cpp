#include "Vector2D.h"

void translateVectors(Vector2D * v1, Vector2D * v2)
{
	v1 -> x += v2 -> x;
	v1 -> y += v2 -> y;
}

