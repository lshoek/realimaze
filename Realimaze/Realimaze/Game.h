#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include <glut.h>
#include "Game.h"
#include "Maze.h"
#include "Ball.h"
#include "EnginePhys.h"
#include "ObjectLoader.h"
#include "Orientation.h"
#include "Texture.h"

class Game
{
	Orientation orientation;
	Maze maze;
	EnginePhys enphys;
	Ball ball;

public:
	GLfloat rx, ry, rz;

	Game(int w, int h);
	~Game();

	void launchGame();
	void endGame();
	void rotateYaw(float rotation);
	void rotatePitch(float rotation);
	void rotateAngle(float rotation);
	void update(float);
	void draw();
	void drawStage(GLfloat idx, GLfloat idy, GLfloat idz);
	void drawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
	string getVars();
	bool isRunning();
};

