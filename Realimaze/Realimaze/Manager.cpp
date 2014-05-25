#include <string>
#include <iostream>
#include <vector>
#include <glut.h>
#include <Windows.h>
#include <thread>

#include "Manager.h"
#include "Game.h"

using namespace std;

void keyHandling(void);
void timerTick(void);

Manager* mngr = NULL;
bool keys[256];
thread keyThread(keyHandling);
thread timer(timerTick);
unsigned long timerTime = 0;

void timerTick(void)
{
	while (true)
	{
		if (mngr -> testGame.isRunning() && mngr -> engine.state == 0)
			timerTime += 10;
		Sleep(10);
	}
}



void keyHandling(void)
{
	while (true)
	{
		if (keys['d'])
		{
			printf("d");
		}
		if (keys[27])//esc
		{
			mngr -> ~Manager();
			mngr->testGame.~Game();
			exit(0);
		}

		Sleep(50);
	}
}

void idleFunc()
{ mngr->update(); }

void displayFunc()
{ mngr->draw(); }

void keyDown(unsigned char key, int x, int y)
{ mngr->kDown(key, x, y); }

void keyUp(unsigned char key, int x, int y)
{ mngr->kUp(key, x, y); }

//Instance of a game. Every game launches a menu first. Stages can be selected from this menu. The menu is left out for the time being.
Manager::Manager() : engine()
{
	mngr = this;
	engine.addSphere(0, 0, 10, &engine.spheres);
	engine.makeSpaceForLines(1);
	engine.addLine(0, 40, 80, 0);
	int i = 0;
	for (; i < 15; i++)
		engine.Step(0,20);
	/*glEnable(GL_DEPTH_TEST); //Instead of glutInit
	glutInitWindowSize(SCRN_WIDTH, SCRN_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Realimaze");
	
	//Register callbacks
	glutIdleFunc(&idleFunc);
	glutDisplayFunc(&displayFunc);
	glutKeyboardFunc(&keyDown);
	glutKeyboardUpFunc(&keyUp);
	testGame.launchGame();
	glutMainLoop();*/
}

Manager::~Manager()
{
	delete mngr;
	keyThread.join();
	timer.join();
}

void Manager::update(void)
{
	testGame.update();
	glutPostRedisplay();
}

void Manager::draw(void)
{
	if (testGame.isRunning())
		testGame.draw(engine.spheres);
	else
	{
		// ORTHOGONAL
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glOrtho(0, SCRN_WIDTH, 0, SCRN_HEIGHT, -1, 200);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//draw 2D here (menu)
	}
	glutSwapBuffers();
}

void Manager::kDown(unsigned char key, int x, int y)
{
	keys[key] = true;
}

void Manager::kUp(unsigned char key, int x, int y)
{
	keys[key] = false;
}