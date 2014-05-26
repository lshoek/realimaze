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
	int state = 0;//0 = in game, -1 = lost, 1 = won
	Vector2D center;
	
	Engine() : center(480/2,640/2)
	{
		state = 0;
	}
	~Engine()
	{

	}
	bool makeSpaceForLines(int size);
	void addLine(float x1, float y1, float x2, float y2);
	void addSphere(float x, float y, float r, vector<Sphere> * vector);
	void Step(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, int sizes[4]);
	void Engine::MoveBall(float direction, float angle, Sphere * sphere);
};


#endif
