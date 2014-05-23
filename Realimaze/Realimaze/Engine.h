#ifndef ENGINE
#define ENGINE

#include "Circle.h"

class Engine
{
public:
	Circle circle;
	Engine(float x, float y, float r) : circle(x, y ,r)
	{
		
	}
	~Engine()
	{

	}
	void MoveBall(float direction, float angle);
};


#endif
