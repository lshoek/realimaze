#ifndef ENGINE
#define ENGINE

#include "Sphere.h"
#include <vector>

using namespace std;

class Engine
{
public:
	vector<Sphere> spheres;
	vector<Line> lines;
	vector<Sphere> holes;
	vector<Sphere> finishes;
	int state;//0 = in game, -1 = lost, 1 = won
	
	Engine()
	{
		
	}
	~Engine()
	{

	}
	bool makeSpaceForLines(int size);
	void addLine(float x1, float y1, float x2, float y2);
	void addSphere(float x, float y, float r, vector<Sphere> * vector);
	void Step(float direction, float angle);
	void Engine::MoveBall(float direction, float angle, Sphere * Sphere);
};


#endif
