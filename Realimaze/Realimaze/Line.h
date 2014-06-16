#ifndef LINE
#define LINE

#include "Shape.h"
#include "Vector2D.h"

class Line //wall
{
public:
	float a;
	float b;
	int state = 0;//0 -> default, 1 -> l:y=ax+b, 2 -> end.y == start.y, 3 -> end.x == start.x, 4 -> start == end
	Vector2D start;
	Vector2D end;
	void translate(Vector2D offset);
	Line(float x1, float y1, float x2, float y2) : start(x1, y1), end(x2,y2)
	{
		CalculateLine();
	}
	~Line()
	{
		
	}
	void CalculateLine(void);
};


#endif