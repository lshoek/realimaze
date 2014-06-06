#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include <glut.h>
#include <vector>
#include "Game.h"
#include "Maze.h"
#include "ObjectLoader.h"
#include "Orientation.h"
#include "Texture.h"
#include "Engine.h"
#include "Sphere.h"

class Game
{
	ObjectLoader objloader;
	Orientation orientation;
	Maze maze;
	Engine engine;

public:
	GLfloat rx, ry, rz;

	int lastFrameTime = 0;
	double timeFac = 0;

	Game(int w, int h);
	~Game();

	void launchGame();
	void endGame();

	void rotateYaw(float rotation);
	void rotatePitch(float rotation);
	void update(float);
	void drawStage(GLfloat idx, GLfloat idy, GLfloat idz);

	void drawSphere(const Sphere * sphere);
	void draw(const vector<Sphere> spheres);

	void drawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
	string getVars();
	bool isRunning();
	void keyHandling(void);
};

