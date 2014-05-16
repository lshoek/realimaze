#ifndef SHAPE
#define SHAPE

#include "Vector2D.h"

class Shape
{
public:
	virtual void translate(Vector2D offset) = 0;
};
#endif
