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

using namespace std;

GLfloat x = 0, y = 5, z = 1;
Texture wood_texture{ "resources/wood_texture.jpg" };
int scrnWidth, scrnHeight;
bool running = false;

Game::Game(int w, int h)
{
	rx = 0; ry = 0; rz = 0;
	scrnWidth = w;
	scrnHeight = h;
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
	glViewport(0, 0, scrnWidth, scrnHeight);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ORTHOGONAL
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glOrtho(0, scrnWidth, 0, scrnHeight, -1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	displayImage();

	// PERSPECTIVE
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluPerspective(20, scrnWidth / (float)scrnHeight, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
	drawStage(-0.5, 0, -0.5);
}

void Game::displayImage()
{
	orientation.modifyImage();
	Texture img{ orientation.getVideoImage() };
	glBindTexture(GL_TEXTURE_2D, img.getTextureId());
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(0, 0);
	glTexCoord2f(0, 1.0);	glVertex2f(0, scrnHeight);
	glTexCoord2f(1.0, 1.0); glVertex2f(scrnWidth, scrnHeight);
	glTexCoord2f(1.0, 0);	glVertex2f(scrnWidth, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Game::drawStage(GLfloat idx, GLfloat idy, GLfloat idz)
{
	glPushMatrix();
	glTranslatef(idx, idy, idz);
	glTranslatef(0.5f, -0.2f, 0.5f);
	glRotatef(rx, 1, 0, 0);
	glRotatef(rz, 0, 0, 1);
	glTranslatef(-0.5, 0.2f, -0.5);

	glBindTexture(GL_TEXTURE_2D, wood_texture.getTextureId());
	glEnable(GL_TEXTURE_2D);

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
}

string Game::getVars()
{
	stringstream strs;
	strs << "rx" << rx << " ry=" << ry << " rz=" << rz << endl;
	return strs.str();
}

bool Game::isRunning()
{
	return running;
}