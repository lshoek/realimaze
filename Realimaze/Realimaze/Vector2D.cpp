#include "Vector2D.h"

Vector2D Vector2D::operator + (Vector2D other)
{
	return Vector2D(this->x + other.x, this->y + other.y);
}
