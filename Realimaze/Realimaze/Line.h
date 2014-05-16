#ifndef LINE
#define LINE

#include "Shape.h"
#include "Vector2D.h"

class Line : public Shape //wall
{
public:
	Vector2D start;
	Vector2D end;
	void translate(Vector2D offset);
	Line();
	~Line();
};

void Line::translate(Vector2D offset)
{

}
#endif