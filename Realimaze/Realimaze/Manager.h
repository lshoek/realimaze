#pragma once
#define SCRN_WIDTH	640
#define SCRN_HEIGHT	480
#include <string>
#include <iostream>
#include <vector>
#include <glut.h>
#include "Manager.h"
#include "Game.h"

class Manager
{
	public:
		Manager();
		~Manager();
		Game testGame{SCRN_WIDTH, SCRN_HEIGHT};
		void update();
		void draw();
		void drawText(const string, const GLfloat, const GLfloat, const float);
		void kDown(unsigned char key, int x, int y);
		void kUp(unsigned char key, int x, int y);

	private:
		int iglut = 0;
		void launchStage();
};
