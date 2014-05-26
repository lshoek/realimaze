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

GLfloat x = 0, y = 5, z = 1, rotation = 0;
int scrnWidth, scrnHeight;
bool running = false;
Texture woodtex{ "resources/wood_texture.jpg" };

Game::Game(int w, int h)
{
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
	drawStage(-0.5, 0, -0.5, 0, 0, 1);
}

void Game::drawStage(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz)
{
	glPushMatrix();
	glTranslatef(idx, idy, idz);
	glTranslatef(0.5f, 0, 0.5f);
	glRotatef(rotation, rx, ry, rz);
	glTranslatef(-0.5, 0, -0.5);

	GLuint textureId = woodtex.getTextureId();
	glBindTexture(GL_TEXTURE_2D, textureId);

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

bool Game::isRunning()
{
	return running;
}