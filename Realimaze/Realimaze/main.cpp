#include <stdlib.h>
#include <glut.h>
#include <gl/GL.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h> 
#include <iostream>

#include "Manager.h"
#include "Line.h"
#include "Sphere.h"
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	//Manager testMngr{};
	Sphere sphere(0, 0, 2);
	Sphere s2(0, 0, 0);
	Line line(-8,10,8,30);
	printf("%d\n", line.state);
	int k = 0;
	long i = 0;
	unsigned long startTime = time(NULL);
	for (k = 0; k < 300; k++)
	{
		for (i= 0; i < 300000; i++)
		{
			sphere.intersectSphere(&s2);
		}
	}
	printf("\ntijd voor 300*300000: %d", time(NULL) - startTime);
	cin.get();
	return 0;
}
