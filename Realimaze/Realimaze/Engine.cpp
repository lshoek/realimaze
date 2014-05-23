#include "Engine.h"
#include "Line.h"
#include "Circle.h"
#include "Vector2D.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

using namespace std;



//direction = de richting waar het bord over is gekanteld
//angle = de hoek waar het bord over is gedraaid
//
void Engine::MoveBall(float direction, float angle)
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
	vToMove = vToMove + circle.distanceRolled;
	vToMove = vToMove * 0.8;
	vToMove.Rotate(direction);
	circle.translate(vToMove);
	circle.distanceRolled = vToMove;// -circle.distanceRolled;
	//move

	//check for the endpoint

	//check for holes 

	//check for walls
	printf("positie:%f,%f, distance rolled %f,%f\n", circle.position.x, circle.position.y, circle.distanceRolled.x, circle.distanceRolled.y);
}

