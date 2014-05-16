#ifndef LINE
#define LINE

#include "Shape.h"
#include "Vector2D.h"

class Line //wall
{
public:
	Vector2D start;
	Vector2D end;
	void translate(Vector2D offset);
	Line(float x1, float y1, float x2, float y2) : start(x1, y1), end(x2,y2)
	{
	}
	~Line()
	{
		
	}
};


#endif