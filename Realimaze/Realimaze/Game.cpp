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
// begin lesley deel
using namespace std;

GLfloat x = 0, y = 5, z = 1;
Texture wood_texture{ "resources/wood_texture.jpg" };
int scrnWidth, scrnHeight;
bool running = false;
// eind lesley deel

Game::Game(int w, int h)
{
	// begin lesley deel
	rx = 0; ry = 0; rz = 0;
	scrnWidth = w;
	scrnHeight = h;
	// eind lesley deel
}

Game::~Game()
{}

void Game::launchGame()
{
	running = true;
}

void Game::endGame()
{
	running = false;
}

void Game::rotateYaw(float rotation)
{
	rx += rotation;
}

void Game::rotatePitch(float rotation)
{
	rz += rotation;
}

void Game::update(float tfac)
{
	glutPostRedisplay();
}

void Game::draw()
{
	// begin lesley deel
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
	drawStage(-0.5, 0, -0.5);
	// eind lesley deel
}

void Game::drawStage(GLfloat idx, GLfloat idy, GLfloat idz)
{
	// begin lesley deel
	glPushMatrix();
	glTranslatef(idx, idy, idz);
	glTranslatef(0.5f, -0.2f, 0.5f);
	glRotatef(rx, 1, 0, 0);
	glRotatef(rz, 0, 0, 1);
	glTranslatef(-0.5, 0.2f, -0.5);

	glBindTexture(GL_TEXTURE_2D, wood_texture.getTextureId());

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(1, 0.2, 0);
	glVertex3f(1, 0, 0);
	glColor3f(1, 1, 1);
	glEnd();
	
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0.2, 0);
	glTexCoord2f(0, 1); glVertex3f(1, 0.2, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 0.2, 1);
	glTexCoord2f(1, 0); glVertex3f(0, 0.2, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(0, 0.2, 1);
	glVertex3f(0, 0, 1);
	glColor3f(1, 1, 1);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(1, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 1);
	glTexCoord2f(1, 0); glVertex3f(0, 0, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0.2, 0);
	glVertex3f(1, 0.2, 1);
	glColor3f(1, 1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0.2, 1);
	glVertex3f(0, 0.2, 1);
	glVertex3f(0, 0, 1);
	glColor3f(1, 1, 1);
	glEnd();
	glPopMatrix();
	// eind lesley deel
}

string Game::getVars()
{
	// begin lesley deel
	stringstream strs;
	strs << "rx" << rx << " ry=" << ry << " rz=" << rz << endl;
	return strs.str();
	// eind lesley deel
}

bool Game::isRunning()
{
	return running;
}