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
<<<<<<< ours
#include "Texture.h"
=======
#include "Engine.h"
#include "Sphere.h"
>>>>>>> theirs

class Game
{
	ObjectLoader objloader;
	Orientation orientation;
	Maze maze;
	Engine engine;

public:
<<<<<<< ours
	GLfloat rx, ry, rz;

=======
	int lastFrameTime = 0;
	double timeFac = 0;

>>>>>>> theirs
	Game(int w, int h);
	~Game();

	void launchGame();
	void endGame();
<<<<<<< ours
	void rotateYaw(float rotation);
	void rotatePitch(float rotation);
	void update(float);
	void draw();
	void drawStage(GLfloat idx, GLfloat idy, GLfloat idz);
=======
	void update();
	void drawSphere(const Sphere * sphere);
	void draw(const vector<Sphere> spheres);
	void drawStage(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
>>>>>>> theirs
	void drawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
	string getVars();
	bool isRunning();
	void keyHandling(void);
};

