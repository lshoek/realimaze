#include <stdlib.h>
#include <glut.h>
#include <gl/GL.h>
#include "Engine.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h> 
#include <iostream>

#include "Line.h"
#include "Circle.h"

using namespace std;

int main(int argc, char* argv[])
{
	Engine engine(0,0,10);
	engine.Step(0, 45);
	engine.Step(0, 45);
	engine.Step(0, 45);
	engine.Step(0, 45);
	//engine.Step(0, 70);
	engine.Step(0, -45);
	engine.Step(0, -45);
	engine.Step(0, -45);
	engine.Step(0, -45);
	engine.Step(0, 0);
	Line line(10, 10, 20, 20);
	Circle c(10, 5, 5);
	printf("%d\n",c.intersectLine(&line));
	printf("%f,%f", line.a, line.b);
	cin.get();
	return 0;
}
