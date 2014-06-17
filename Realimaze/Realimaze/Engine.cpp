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
float deltaX = 0, deltaY = 0;
float pitch, yaw;
bool run = false;
float sphereX = 0, sphereY = 0, sphereXOld = 0, sphereYOld = 0;

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
			/*if (y > 0)//onder 
			{
				factorY = y * MAX_ROTATION;
			}
			/*x = deltaX - eng->centre.x; // centre which is set in the constructor
			y = deltaY - eng->centre.y; // centre which is set in the constructor
			float angleX, angleY, factorX = 0, factorY = 0; // local variables to use in this function
			//340, 218
			if (y > 0)//onder 
			{
				//24 graden 285
				factorY = y * ((285 - 218) / 24); // uses the first values given when the screen was bigger
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
				//28 graden 280
				factorX -= x * ((340 - 280) / 28);
			}*/
			int j;

			pitch = deltaY * MAX_ROTATION;
			yaw = deltaX * -MAX_ROTATION;

			for (j = 0; j < eng->spheres.size(); j++) // collects all spheres, only one in the game though
			{
				printf("angleX, angleY %f,%f\n", yaw, pitch); // prints the data from the sphere
				eng->MoveBall(&yaw, &pitch, &eng->spheres.at(j)); // calls the function moveball in this class
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

// Constructor for Engine, sets default values for the x and y as center position
Engine::Engine()// nieuwe x en y is 53 en 70
{
	state = 0;
	eng = this;
}

// Adds a sphere to spheres in the class Engine
void Engine::addSphere(float x, float y, float r, vector<Sphere> * vector)
{
	vector->reserve(1);
	Sphere c(x, y, r);
	vector->push_back(c);
}

void Engine::Step(float x, float y)
{
	if (eng == nullptr)
		eng = this;
	deltaX = x;
	deltaY = y;
	if (state != 0)
		return;
	run = true;
}

//angleX en angleY = de hoek waar het bord over is gedraaid
//
void Engine::MoveBall(float * angleX, float * angleY, Sphere * sphere)
{
	sphereXOld = sphere->position.x;
	sphereYOld = sphere->position.y;
	//angle en direction naar radialen rekenen
	*angleX = *angleX /180 * M_PI;
	*angleY = *angleY / 180 * M_PI;
	//calculate vector to move
	//start at (0,0)
	Vector2D vToMove(10 * sin(*angleX), 10 * sin(*angleY)); // local vector
	//calculate vector to move to
	//with gravity
	//the position of the Sphere = deltaDistance + position Sphere
	vToMove = vToMove + sphere -> distanceRolled; // local vector initialized in this function
	vToMove = vToMove * 0.8;
	//vToMove.Rotate(direction);
	Vector2D vx = vToMove;
	vx.y = 0;
	sphere -> translate(vx);
	sphere -> distanceRolled = vToMove;
	bool rollx = true;
	bool rolly = true;

	if (!(sphere->position.x <= 110 && sphere->position.x >= -110))
	{
		rollx = false;
	}
	else if (!(sphere->position.y <= 75 && sphere->position.y >= -75))
	{
		rolly = false;
	}

	//check for the endpoint
	int j;
	for (j = 0; j < finishes.size(); j++) // finishes = vector<Sphere> (not sure why needed)
	{
		if (sphere->intersectSphere(&finishes.at(j)))
		{
			rollx = false;
			state = 1;
		}
	}
	//check for holes 
	for (j = 0; j < holes.size(); j++) // holes = vector<Sphere> (vector with the holes in it)
	{
		if (sphere->intersectSphere(&spheres.at(j))) // checks if the sphere intersects with a sphere? :o
		{
			rollx = false;
			state = -1;
		}
	}
	//check for walls
	for (j = 0; j < lines.size(); j++)
	{
		if (sphere->intersectLine(&lines.at(j))) // checks for intersections with a wall
			rollx = false;
	}
	sphere->translate(vx * -1);
	
	Vector2D vy = vToMove;
	vy.x = 0;
	sphere->translate(vy);

	//check for the endpoint
	for (j = 0; j < finishes.size(); j++) // finishes = vector<Sphere> (not sure why needed)
	{
		if (sphere->intersectSphere(&finishes.at(j)))
		{
			rolly = false;
			state = 1;
		}
	}
	//check for holes 
	for (j = 0; j < holes.size(); j++) // holes = vector<Sphere> (vector with the holes in it)
	{
		if (sphere->intersectSphere(&spheres.at(j))) // checks if the sphere intersects with a sphere? :o
		{
			rolly = false;
			state = -1;
		}
	}
	//check for walls
	for (j = 0; j < lines.size(); j++)
	{
		if (sphere->intersectLine(&lines.at(j))) // checks for intersections with a wall
			rolly = false;
	}
	sphere->translate(vy * -1);


	if (rollx && rolly)
	{
		sphere->translate(vToMove);
	}
	else
	{
		if (rolly)
		{
			sphere->translate(vy);
			sphere->distanceRolled.y = 0;
		}
		if (rollx)
		{
			sphere->translate(vx);
			sphere->distanceRolled.x = 0;
		}
	}
	printf("positie:%f,%f, distance rolled %f,%f\n", sphere->position.x, sphere->position.y, sphere->distanceRolled.x, sphere->distanceRolled.y);
}

/*
x1,y1 = start position
x2,y2 = end position
*/
// function to add a 'wall'
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
