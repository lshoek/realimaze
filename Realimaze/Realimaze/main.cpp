#include <stdlib.h>
#include <glut.h>
#include <gl/GL.h>
#include "Engine.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h> 
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	Engine engine(0,0,10);
	engine.MoveBall(10, 45);
	engine.MoveBall(10, 45);
	engine.MoveBall(10, 45);
	engine.MoveBall(10, 45);
	//engine.MoveBall(0, 70);
	engine.MoveBall(10, -45);
	engine.MoveBall(10, -45);
	engine.MoveBall(10, -45);
	engine.MoveBall(10, -45);
	engine.MoveBall(0, 0);
	cin.get();
	return 0;
}
