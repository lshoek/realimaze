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
	const float RADIUSBALL = 10;
	Vector2D centre;
	Engine() : centre(0, 0)
	{
		state = 0;
	}
	~Engine()
	{

	}
	bool makeSpaceForLines(int size);
	void addLine(float x1, float y1, float x2, float y2);
	void addSphere(float x, float y, float r, vector<Sphere> * vector);
	void MoveBall(float angleX, float angleY, Sphere * sphere);
	void Step(float deltaX, float deltaY);
};


#endif