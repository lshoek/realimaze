#include <vector>
#include <iostream>
#include <functional>
#include <glut.h>
#include "Game.h"
<<<<<<< ours
#include "Maze.h"
#include "Ball.h"
#include "EnginePhys.h"
#include "ObjectLoader.h"
#include "Orientation.h"
#include "Texture.h"

=======
#include <thread>
#include <windows.h>
>>>>>>> theirs
using namespace std;

<<<<<<< ours
GLfloat x = 0, y = 5, z = 1;
Texture wood_texture{ "resources/wood_texture.jpg" };
=======
void timerTick(void);


GLfloat x = 0, y = 5, z = 1, rotation = 0;
>>>>>>> theirs
int scrnWidth, scrnHeight;
bool running = false;



Game::Game(int w, int h)
{
	rx = 0; ry = 0; rz = 0;
	scrnWidth = w;
	scrnHeight = h;
}


Game::~Game()
{
	
}

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
<<<<<<< ours
	glutPostRedisplay();
=======
	int time = glutGet(GLUT_ELAPSED_TIME);
	timeFac = (time - lastFrameTime) / 1000.0;
	lastFrameTime = time;
	rotation+=0.05;
>>>>>>> theirs
}

void Game::draw(const vector<Sphere> spheres)
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
<<<<<<< ours
	drawStage(-0.5, 0, -0.5);
=======
	drawStage(-0.5, 0, -0.5, 0, 0, 1);
	int j = 0;
	for (; j < spheres.size(); j++)
	{
		drawSphere(&spheres.at(j));

	}
}

void Game::drawSphere(const Sphere * sphere)
{
	
>>>>>>> theirs
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