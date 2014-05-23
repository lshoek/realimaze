#include "Vector3D.h"
#include <math.h>

Vector3D Vector3D::operator + (Vector3D other)
{
	return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3D Vector3D::operator - (Vector3D other)
{
	return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3D Vector3D::operator * (float factor)
{
	return Vector3D(this->x * factor, this->y * factor, this->z * factor);
}

Vector3D Vector3D::operator / (float factor)
{
	return Vector3D(this->x / factor, this->y / factor, this->z / factor);
}