#include "Vector2D.h"
#include <stdio.h>
#include <math.h>

void Vector2D::Rotate(float angle)
{
	this->x = this->x * cos(angle) - this->y*sin(angle);
	this->y = this->x * sin(angle) + this->y*cos(angle);

	
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

bool operator ==(const Vector2D v1, const Vector2D v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

bool operator !=(const Vector2D v1, const Vector2D v2)
{
	return (v1.x != v2.x && v1.y != v2.y);
}

bool operator <(const Vector2D v1, const Vector2D v2)
{
	printf("%d\n", pow(v1.x, 2) + pow(v1.y, 2)) < (pow(v2.x, 2) + pow(v2.y, 2));
	return (pow(v1.x, 2) + pow(v1.y, 2)) < (pow(v2.x, 2) + pow(v2.y, 2));
}

bool operator >(const Vector2D v1, const Vector2D v2)
{
	return (pow(v1.x, 2) + pow(v1.y, 2)) > (pow(v2.x, 2) + pow(v2.y, 2));
}
