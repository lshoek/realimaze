#include "Engine.h"
#include "Line.h"
#include "Sphere.h"
#include "Vector2D.h"
#include "globaldefines.h"
#include "ObjectLoader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <vector>
#include <Windows.h>
#include <thread>

using namespace std;
Engine * eng = nullptr;
bool run = false;

void checkCollision(void);
thread collisionthread(checkCollision);

void checkCollision(void)
{
	printf("igor vssdfzsdfgxdgfgfawesf\n");
	while (eng == nullptr)
	{
		printf("nul-nul\n");
		Sleep(10);
	}
	while (eng->ortn == nullptr)
	{
		Sleep(10);
	}
	float x, y;
	clock_t time1 = clock();
	clock_t time2 = clock();
	while (true)
	{		
		while ((float) time1 - (float) time2 < CLOCKS_PER_SEC/50)
		{
			time1 = clock();
			Sleep(1);
		}
		if (run)
		{
			PosF pos = eng -> ortn -> getOrientationFactor();
			int j;//loop index in the end
			x = pos.xPos;
			y = pos.yPos;
			float factorX = 0, factorY = 0;
			if (y > 0)//onder 
			{
				factorY = y * MAX_ROTATION;
			}
			else if (y < 0)//boven	
			{
				factorY -= y * MAX_ROTATION;
			}
			if (x > 0)//rechts
			{
				factorX = x * MAX_ROTATION;
			}
			else if (x < 0)//links
			{
				factorX -= x * MAX_ROTATION;
			}
			for (j = 0; j < eng->spheres.size(); j++)
			{
				printf("angleX, angleY %f,%f\n", factorX, factorY);
				eng->MoveBall(&factorX, &factorY, &eng->spheres.at(j));
			}
		}
		run = false;
		time2 = clock();
	}
}

/*
x, y = position of the centre
r = radius (voor een finish of gat is het nodig om van te voren de radius hiervan af halen
vector = a vector in Engine to put the Sphere in (Spheres/holes/finishes)
*/
Engine::Engine()
{
	state = 0;
	eng = this;
}

void Engine::addSphere(float x, float y, float r, vector<Sphere> * vector)
{
	vector->reserve(1);
	Sphere c(x, y, r);
	vector->push_back(c);
}

void Engine::Step(void)
{
	if (eng == nullptr)
		eng = this;
	if (state != 0)
		return;
	run = true;
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

//void Engine::AddLinesFromFaces(const vector<::Vec3f> * vectors)
//{

//}
