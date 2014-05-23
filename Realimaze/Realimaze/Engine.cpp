#include "Engine.h"
#include "Line.h"
#include "Circle.h"
#include "Vector2D.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <vector>

using namespace std;

void Engine::addCircle(float x, float y, float r, vector<Circle> * vector)
{
	vector->reserve(1);
	Circle c(x, y, r);
	vector->push_back(c);
}


void Engine::Step(float direction, float angle)
{
	int j;
	for (j = 0; j < circles.size(); j++)
	{
		MoveBall(direction, angle, &circles.at(j));
	}
}

//direction = de richting waar het bord over is gekanteld
//angle = de hoek waar het bord over is gedraaid
//
void Engine::MoveBall(float direction, float angle, Circle * circle)
{
	//angle en direction naar radialen rekenen
	direction = direction/180 * M_PI;
	angle = angle/180 * M_PI;
	//calculate vector to move
	//start at (0,0)
	Vector2D vToMove(0, 0);
	//calculate vector to move to
	//with gravity
	
	Vector2D gravitySpeed(0,10);
	gravitySpeed = gravitySpeed * (sin(angle));//volgens wikipedia
	//circle : oldSpeed = old speed + new vector
	//the position of the circle = deltaDistance + position circle
	vToMove = vToMove + gravitySpeed;
	vToMove = vToMove + circle -> distanceRolled;
	vToMove = vToMove * 0.8;
	vToMove.Rotate(direction);
	circle -> translate(vToMove);
	circle -> distanceRolled = vToMove;// -circle.distanceRolled;
	bool roll = true;
	//move

	//check for the endpoint
	int j;
	for (j = 0; j < finishes.size(); j++)
	{
		if (circle->intersectCircle(&finishes.at(j)))
		{
			roll = false;
			circle->state = 1;
		}
	}
	//check for holes 
	for (j = 0; j < holes.size(); j++)
	{
		if (circle->intersectCircle(&circles.at(j)))
		{
			roll = false;
			circle->state = -1;
		}
	}
	//check for walls
	for (j = 0; j < lines.size(); j++)
	{
		if (circle->intersectLine(&lines.at(j)))
			roll = false;
	}
	if (!roll)
	{
		circle->translate(vToMove * -1);
		circle->distanceRolled.x = 0;
		circle->distanceRolled.y = 0;
	}
	printf("positie:%f,%f, distance rolled %f,%f\n", circle -> position.x, circle -> position.y, circle -> distanceRolled.x, circle -> distanceRolled.y);
}

bool Engine::makeSpaceForLines(int size)
{
	lines.reserve(size);
	return true;
}

void Engine::addLine(float x1, float y1, float x2, float y2)
{
	Line l(x1, y1, x2, y2);
	lines.push_back(l);
}