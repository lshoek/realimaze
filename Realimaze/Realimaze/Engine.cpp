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
x, y = position of the centre
r = radius (voor een finish of gat is het nodig om van te voren de radius hiervan af halen
vector = a vector in Engine to put the Sphere in (Spheres/holes/finishes)
*/
void Engine::addSphere(float x, float y, float r, vector<Sphere> * vector)
{
	vector->reserve(1);
	Sphere c(x, y, r);
	vector->push_back(c);
}

void Engine::Step(float deltaX, float deltaY)
{
	if (state != 0)
		return;
	int j;//loop index in the end
	deltaX -= centre.x;
	deltaY -= centre.y;
	float angleX, angleY, factorX = 0, factorY = 0;		
	//340, 218
	if (deltaY > 0)//onder 
	{
		//24 graden 285
		factorY = deltaY * ((285-218)/24);
	}
	else if(deltaY < 0)//boven	
	{
		//29 graden 150
		factorY -= deltaY * ((218 - 150) / 29);
	}
	if (deltaX > 0)//rechts
	{
		//35 graden 400
		factorX = deltaX * ((400 - 340) / 35);
	}
	else if(deltaX < 0)//links
	{
		//28 graden 280
		factorX -= deltaX * ((340 - 280) / 28);
	}
	angleX = (deltaX * factorX);
	angleY = (deltaY * factorY);
	for (j = 0; j < spheres.size() && state == 0; j++)
	{
		printf("angleX, angleY %f,%f\n", angleX, angleY);
		MoveBall(&angleX, &angleY, &spheres.at(j));
	}
}

//angleX en angleY = de hoek waar het bord over is gedraaid
//
void Engine::MoveBall(float * angleX, float * angleY, Sphere * sphere)
{
	//angle en direction naar radialen rekenen
	*angleX = *angleX /180 * M_PI;
	*angleY = *angleY / 180 * M_PI;
	//calculate vector to move
	//start at (0,0)
	Vector2D vToMove(10 * sin(*angleX), 10 * sin(*angleY));
	//calculate vector to move to
	//with gravity
	//the position of the Sphere = deltaDistance + position Sphere
	vToMove = vToMove + sphere -> distanceRolled;
	vToMove = vToMove * 0.8;
	//vToMove.Rotate(direction);
	sphere -> translate(vToMove);
	sphere -> distanceRolled = vToMove;
	bool roll = true;

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
	printf("positie:%f,%f, distance rolled %f,%f\n", sphere->position.x, sphere->position.y, sphere->distanceRolled.x, sphere->distanceRolled.y);
}

/*
x1,y1 = start position
x2,y2 = end position
*/
void Engine::addLine(float x1, float y1, float x2, float y2)
{
	if (lines.size() % 10 == 0)
	{
		lines.reserve(10);
	}
	Line l(x1, y1, x2, y2);
	lines.push_back(l);
}

void Engine::AddLinesFromFaces(const vector<Vec3f> * vectors)
{
	int i = 0;
	for (; i < vectors->size(); i++)
	{

	}
}