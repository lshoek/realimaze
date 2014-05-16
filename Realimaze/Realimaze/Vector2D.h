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
	Vector2D operator +(Vector2D other);
};
#endif
