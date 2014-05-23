#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include <glut.h>
#include "Game.h"
#include "Maze.h"
#include "Ball.h"
#include "ObjectLoader.h"
#include "Orientation.h"
#include "Engine.h"

class Game
{
	ObjectLoader objloader;
	Orientation orientation;
	Maze maze;
	Engine engine;
	Ball ball;
	

public:
	

	Game(int w, int h);
	~Game();
	void launchGame();
	void endGame();
	void update();
	void draw();
	void drawStage(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
	void drawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
	bool isRunning();
	void keyHandling(void);
};
