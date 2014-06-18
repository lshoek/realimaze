#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include <glut.h>
#include <vector>
#include "Game.h"
#include "Maze.h"
#include "Orientation.h"
#include "Texture.h"
#include "globaldefines.h"
#include "Engine.h"
#include "Sphere.h"

class Game
{
	// begin lesley deel
	Maze maze;
	Engine enphys;
	//Sphere ball;
	// eind lesley deel

public:
	int lastFrameTime = 0;
	double timeFac = 0;
	// begin lesley deel
	Orientation orientation;
	Engine engine;
	GLfloat x = 0, y = 5, z = 1, yaw = 0, pitch = 0;
	bool running = false, video_on = VIDEO_ON;

	Game(int w, int h);
	~Game();

	void launchGame();
	void endGame();

	void rotateYaw(float rotation);
	void rotatePitch(float rotation);
	void update(float);

	void displayImage();
	void drawStage(GLfloat idx, GLfloat idy, GLfloat idz,const vector<Sphere> spheres);
	void update();
	void drawSphere(const Sphere * sphere);
	void draw(const vector<Sphere> spheres);
	void drawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);
	string getVars();
	bool isRunning();
	// eind lesley deel
	void keyHandling(void);
	void openCV(void);
};

