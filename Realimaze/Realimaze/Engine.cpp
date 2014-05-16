#include "Engine.h"
#include "Line.h"
#include "Circle.h"
#include "Vector2D.h"
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

using namespace std;



//direction = de hoek waar het bord over is gekanteld
//
void Engine::MoveBall(float direction, Vector2D distance)
{
	//calculate vector to move
	//start at (0,0)
	//calculate vector to move to
	//circle : deltaDistance = old speed + new vector
	//friction = (for example) 0.2 * deltaDistance
	//circle : deltaDistance -= friction
	//the position of the circle = deltaDistance + position circle

	//move

	//check for the endpoint

	//check for holes 

	//check for walls

}

