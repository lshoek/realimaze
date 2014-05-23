#include "Vector2D.h"
#include <math.h>

void Vector2D::Rotate(float angle)
{
	this->x = this->x * cos(angle) - this->y*sin(angle);
	this->y = this->x*sin(angle) + this->y*cos(angle);
}

Vector2D Vector2D::operator + (Vector2D other)
{
	return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator - (Vector2D other)
{
	return Vector2D(this->x - other.x, this->y - other.y);
}

Vector2D Vector2D::operator * (float factor)
{
	return Vector2D(this->x * factor, this->y * factor);
}

Vector2D Vector2D::operator / (float factor)
{
	return Vector2D(this->x / factor, this->y / factor);
}