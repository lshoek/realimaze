#pragma once

#include "Sphere.h"
#include "Orientation.h"
#include <vector>

using namespace std;

class Engine
{
public:
	vector<Sphere> spheres;
	vector<Line> lines;
	vector<Sphere> holes;
	vector<Sphere> finishes;
	Orientation * ortn = nullptr;
	int state = 0;//0 = in game, -1 = lost, 1 = won
	const float RADIUSBALL = 10;
	Engine();
	~Engine()
	{

	};
	void addLine(float x1, float y1, float x2, float y2);
	void addSphere(float x, float y, float r, vector<Sphere> * vector);
	void MoveBall(float * angleX, float * angleY, Sphere * sphere);
	void Step();
	//void AddLinesFromFaces(const vector<::Vec3f> * vectors);
};
