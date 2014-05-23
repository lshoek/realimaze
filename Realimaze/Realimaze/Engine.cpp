#include "Engine.h"
#include "Line.h"
#include "Sphere.h"
#include "Vector2D.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <vector>

using namespace std;

/*
x, y = position
r = radius
vector = a vector in Engine to put the Sphere in (Spheres/holes/finishes)
*/
void Engine::addSphere(float x, float y, float r, vector<Sphere> * vector)
{
	vector->reserve(1);
	Sphere c(x, y, r);
	vector->push_back(c);
}

/*
direction = de hoek waar de bal heen rolt
angle = de hoek waarover gedraaid is
*/
void Engine::Step(float direction, float angle)
{
	int j;
	for (j = 0; j < spheres.size(); j++)
	{
		MoveBall(direction, angle, &spheres.at(j));
	}
}

//direction = de richting waar het bord over is gekanteld
//angle = de hoek waar het bord over is gedraaid
//
void Engine::MoveBall(float direction, float angle, Sphere * Sphere)
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
	//Sphere : oldSpeed = old speed + new vector
	//the position of the Sphere = deltaDistance + position Sphere
	vToMove = vToMove + gravitySpeed;
	vToMove = vToMove + Sphere -> distanceRolled;
	vToMove = vToMove * 0.8;
	vToMove.Rotate(direction);
	Sphere -> translate(vToMove);
	Sphere -> distanceRolled = vToMove;// -Sphere.distanceRolled;
	bool roll = true;
	//move

	//check for the endpoint
	int j;
	for (j = 0; j < finishes.size(); j++)
	{
		if (Sphere->intersectSphere(&finishes.at(j)))
		{
			roll = false;
			state = 1;
		}
	}
	//check for holes 
	for (j = 0; j < holes.size(); j++)
	{
		if (Sphere->intersectSphere(&spheres.at(j)))
		{
			roll = false;
			state = -1;
		}
	}
	//check for walls
	for (j = 0; j < lines.size(); j++)
	{
		if (Sphere->intersectLine(&lines.at(j)))
			roll = false;
	}
	if (!roll)
	{
		Sphere->translate(vToMove * -1);
		Sphere->distanceRolled.x = 0;
		Sphere->distanceRolled.y = 0;
	}
	printf("positie:%f,%f, distance rolled %f,%f\n", Sphere -> position.x, Sphere -> position.y, Sphere -> distanceRolled.x, Sphere -> distanceRolled.y);
}

//to add lines, you need to make space
//size = number of lines to add
bool Engine::makeSpaceForLines(int size)
{
	lines.reserve(size);
	return true;
}

/*
FIRST CALL makeSpaceForLines!
x1,y1 = start position
x2,y2 = end position
*/
void Engine::addLine(float x1, float y1, float x2, float y2)
{
	Line l(x1, y1, x2, y2);
	lines.push_back(l);
}