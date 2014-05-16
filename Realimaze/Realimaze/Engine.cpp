#include "Engine.h"
#include "Line.h"
#include "Circle.h"
#include "Vector2D.h"
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

using namespace std;

void CreateEngine(void)
{
	circle = (Circle *) malloc(sizeof(Circle));
}

void DestructEngine(void)
{
	free(circle);
}

void Step(void)
{

}