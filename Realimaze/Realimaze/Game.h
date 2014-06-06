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
#include "globaldefines.h"

class Game
{
	// begin lesley deel
	ObjectLoader objloader;
	Maze maze;
	EnginePhys enphys;
	Ball ball;
	// eind lesley deel

public:
	// begin lesley deel
	GLfloat rx, ry, rz;
	Orientation orientation;
	GLfloat x = 0, y = 5, z = 1, yaw = 0, pitch = 0;
	bool running = false, video_on = false;

	Game(int, int);
	Game(){};
	~Game();

	void launchGame();
	void endGame();
	void rotateYaw(float rotation);
	void rotatePitch(float rotation);
	void update(float);
	void draw();
	void displayImage();
	void drawStage(GLfloat idx, GLfloat idy, GLfloat idz);
	void drawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
	string getVars();
	bool isRunning();
	// eind lesley deel
};

