#ifndef ENGINE
#define ENGINE

#include "Circle.h"
#include <vector>

using namespace std;

class Engine
{
public:
	vector<Circle> circles;
	vector<Line> lines;
	vector<Circle> holes;
	vector<Circle> finishes;
	
	Engine(float x, float y, float r)
	{
		addCircle(x, y, r, &circles);
	}
	~Engine()
	{

	}
	bool makeSpaceForLines(int size);
	void addLine(float x1, float y1, float x2, float y2);
	void addCircle(float x, float y, float r, vector<Circle> * vector);
	void Step(float direction, float angle);
	void Engine::MoveBall(float direction, float angle, Circle * circle);
};


#endif
