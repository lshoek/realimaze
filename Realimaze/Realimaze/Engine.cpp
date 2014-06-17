#include "Engine.h"
#include "Line.h"
#include "Sphere.h"
#include "Vector2D.h"
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
			Sleep(2);
		}
		if (run)
		{
			int j;

			pitch = (deltaY * MAX_ROTATION);
			yaw = (deltaX * MAX_ROTATION) *-1;

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
// Constructor for Engine, set variable values for the x and y as center position
Engine::Engine(float x, float y) : centre(x, y)
{
	state = 0;
	eng = this;
}

// Constructor for Engine, sets default values for the x and y as center position
Engine::Engine() : centre(53, 70) // nieuwe x en y is 53 en 70
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

void Engine::Step(float X, float Y)
{
	if (eng == nullptr)
		eng = this;
	if (state != 0)
		return;
	deltaX = X;
	deltaY = Y;
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
	sphere -> translate(vToMove);
	sphere -> distanceRolled = vToMove;

	bool roll;

	if (sphere->position.x <= 110 && sphere->position.x >= -110 && sphere->position.y <= 75 && sphere->position.y >= -75)
	{
		roll = true;
	}
	else
	{
		roll = false;
	}

	//check for the endpoint
	int j;
	for (j = 0; j < finishes.size(); j++) // finishes = vector<Sphere> (not sure why needed)
	{
		if (sphere->intersectSphere(&finishes.at(j)))
		{
			roll = false;
			state = 1;
		}
	}
	//check for holes 
	for (j = 0; j < holes.size(); j++) // holes = vector<Sphere> (vector with the holes in it)
	{
		if (sphere->intersectSphere(&spheres.at(j))) // checks if the sphere intersects with a sphere? :o
		{
			roll = false;
			state = -1;
		}
	}
	//check for walls
	for (j = 0; j < lines.size(); j++)
	{
		if (sphere->intersectLine(&lines.at(j))) // checks for intersections with a wall
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
