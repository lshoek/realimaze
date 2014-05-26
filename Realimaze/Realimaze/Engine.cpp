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

Vector2D delta(0, 0);
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
v1	v2
v3	v4


*/
void Engine::Step(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, int sizes[4])
{
	if (state != 0)
		return;
	int j;
	float direction, angle;
	Vector2D vDir(0, 0);
	Vector2D * v[4] = {&v1, &v2, &v3, &v4};
	if (v1.y == v2.y)
	{
		printf("jemoeder1");

	}
	else if (v1.x == v3.x)
	{
		printf("jemoeder2");
	}
	else if (v3.y == v4.y)
	{
		printf("jemoeder3");
	}
	else if (v4.x == v2.x)
	{
		printf("jemoeder4");
	}
	else
	{
		int idx = 1;
		int smallest = sizes[0];
		for (; idx < 3; idx++)
		{
			if (sizes[idx] < smallest)
				smallest = sizes[idx];
		}
		vDir = vDir + v1 + v2 + v3 + v4 - *v[idx];
		direction = tanhf(vDir.y / vDir.x / 180 * M_PI);
		angle = coshf(vDir.x / center.y / 180 * M_PI);
	}	
	//printf("\nvDir = %f,%f\n", vDir.x, vDir.y);
	for (j = 0; j < spheres.size(); j++)
	{
		//printf("direction angle %f,%f\n", direction, angle);
		MoveBall(direction, angle, &spheres.at(j));
	}
}

//direction = de richting waar het bord over is gekanteld
//angle = de hoek waar het bord over is gedraaid
//
void Engine::MoveBall(float direction, float angle, Sphere * sphere)
{
	//angle en direction naar radialen rekenen
	direction = direction/180 * M_PI;
	angle = angle/180 * M_PI;
	//calculate vector to move
	//start at (0,0)
	Vector2D vToMove(0, 0);
	//calculate vector to move to
	//with gravity
	Vector2D gravitySpeed(10 * sin(angle), 0);
	//gravitySpeed = gravitySpeed );//volgens wikipedia
	//Sphere : oldSpeed = old speed + new vector
	//the position of the Sphere = deltaDistance + position Sphere
	vToMove = vToMove + gravitySpeed;
	vToMove = vToMove + sphere -> distanceRolled;
	vToMove = vToMove * 0.8;
	vToMove.Rotate(direction);
	sphere -> translate(vToMove);
	sphere -> distanceRolled = vToMove;
	bool roll = true;
	//move

	//check for the endpoint
	int j;
	for (j = 0; j < finishes.size(); j++)
	{
		if (sphere->intersectSphere(&finishes.at(j)))
		{
			roll = false;
			state = 1;
		}
	}
	//check for holes 
	for (j = 0; j < holes.size(); j++)
	{
		if (sphere->intersectSphere(&spheres.at(j)))
		{
			roll = false;
			state = -1;
		}
	}
	//check for walls
	for (j = 0; j < lines.size(); j++)
	{
		if (sphere->intersectLine(&lines.at(j)))
			roll = false;
		if (!roll)
			printf("staat stil kut!\n");
	}
	if (!roll)
	{
		sphere->translate(vToMove * -1);
		sphere->distanceRolled.x = 0;
		sphere->distanceRolled.y = 0;
	}
	//, sphere->distanceRolled.x, sphere->distanceRolled.y,sphere->distanceRolled.x- delta.x, sphere->distanceRolled.y-delta.y
	printf("positie:%f,%f, distance rolled %f,%f\n",sphere->position.x, sphere->position.y);
	delta = sphere->distanceRolled;
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