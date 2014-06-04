#ifndef VECTOR2D
#define VECTOR2D

class Vector2D
{
public:
	float x;
	float y;

	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Rotate(float angle);

	Vector2D operator +(Vector2D other);
	Vector2D operator -(Vector2D other);
	Vector2D operator *(float factor);
	Vector2D operator /(float factor);
};

bool operator ==(const Vector2D v1, const Vector2D v2);
bool operator !=(const Vector2D v1, const Vector2D v2);
bool operator <(const Vector2D v1, const Vector2D v2);
bool operator >(const Vector2D v1, const Vector2D v2);
#endif

