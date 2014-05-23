#include <vector>
#include <iostream>
#include <functional>
#include <glut.h>
#include "Game.h"
#include <thread>
#include <windows.h>
using namespace std;

void timerTick(void);


GLfloat x = 0, y = 5, z = 1, rotation = 0;
int scrnWidth, scrnHeight;
bool running = false;
thread timer(timerTick);
unsigned long timerTime = 0;


Game::Game(int w, int h) :engine(0, 0, 10)
{
	scrnWidth = w;
	scrnHeight = h;
}

void timerTick(void)
{
	while (true)
	{
		if (running)
			timerTime += 10;
		Sleep(10);
	}
}

Game::~Game()
{
	timer.join();
}

void Game::launchGame()
{
	running = true;
}

void Game::endGame()
{
	running = false;
}

void Game::update()
{
	rotation+=0.05;
}

void Game::draw()
{
	glViewport(0, 0, scrnWidth, scrnHeight);
	glEnable(GL_DEPTH_TEST);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// PERSPECTIVE
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, scrnWidth / (float)scrnHeight, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
	//drawStage(-0.5, 0, -0.5, 0, 0, 1);
}

void Game::drawStage(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz)
{
	glPushMatrix();
	glTranslatef(idx, idy, idz);
	glTranslatef(0.5f, 0, 0.5f);
	glRotatef(rotation, rx, ry, rz);
	glTranslatef(-0.5, 0, -0.5);

	glBegin(GL_QUADS);
	glColor3f(255, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(1, 0.2, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 255, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(1, 0.2, 0);
	glVertex3f(1, 0.2, 1);
	glVertex3f(0, 0.2, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 255);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(0, 0.2, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(255, 255, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 255, 255);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0.2, 0);
	glVertex3f(1, 0.2, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(255, 0, 255);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0.2, 1);
	glVertex3f(0, 0.2, 1);
	glVertex3f(0, 0, 1);
	glEnd();
	glPopMatrix();
}

bool Game::isRunning()
{
	return running;
}