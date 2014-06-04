#ifndef VECTOR3D
#define VECTOR3D

class Vector3D
{
public:
	float x;
	float y;
	float z;

	Vector3D(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};
	
	Vector3D operator +(Vector3D other);
	Vector3D operator -(Vector3D other);
	Vector3D operator *(float factor);
	Vector3D operator /(float factor);
};
#endif
