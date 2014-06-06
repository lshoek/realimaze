#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <glut.h>
#include "Game.h"
#include "globaldefines.h"

class Manager
{
	public:
		Manager();
		~Manager();
		Game testGame;
		void update();
		void draw();
		void drawText(const string, const GLfloat, const GLfloat, const float);
		void kDown(unsigned char key, int x, int y);
		void kUp(unsigned char key, int x, int y);

	private:
		int iglut = 0;
		void launchStage();
};
