#include <vector>
#include <iostream>
#include <functional>
#include <glut.h>
#include "Game.h"
#include "Maze.h"
#include "ObjectLoader.h"
#include "Orientation.h"
#include "Texture.h"
#include <thread>
#include <windows.h>

// begin lesley deel
using namespace std;

void timerTick(void);
GLfloat x = 0, y = 5, z = 1, rotation = 0;
int scrnWidth, scrnHeight;
bool running = false;
// eind lesley deel

ObjModel* objm;

Game::Game(int w, int h)
{
	// begin lesley deel
	rx = 0; ry = 0; rz = 0;
	scrnWidth = w;
	scrnHeight = h;

	// eind lesley deel
	objm = new ObjModel("models/holes/mazeWithHoles.obj"); 
}


Game::~Game()
{
	
}

void Game::launchGame()
{
	running = true;
	cout << "Bas is lelijk" << endl;
}

void Game::endGame()
{
	running = false;
}

void Game::rotateYaw(float rotation)
{
	yaw += rotation;
}

void Game::rotatePitch(float rotation)
{
	pitch += rotation;
}

void Game::rotateAngle(float rotation)
{
	ry += rotation;
}

void Game::update(float tfac)
{
	yaw = orientation.getOrientationFactor().xPos * 45.0;
	pitch = orientation.getOrientationFactor().yPos * 45.0;
	glutPostRedisplay();

	int time = glutGet(GLUT_ELAPSED_TIME);
	timeFac = (time - lastFrameTime) / 1000.0;
	lastFrameTime = time;
	rotation+=0.05;
}

void Game::draw(const vector<Sphere> spheres)
{
	// begin lesley deel
	//glViewport(0, 0, scrnWidth, scrnHeight);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCRN_WIDTH, SCRN_HEIGHT);
	glClearColor(0.6f, 0.6f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (video_on)
	{
		//ORTHOGONAL
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glOrtho(0, SCRN_WIDTH, 0, SCRN_HEIGHT, -1, 200);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		displayImage();
	}

	// PERSPECTIVE
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*glEnable(GL_DEPTH_TEST);
	gluPerspective(20, SCRN_WIDTH / (float)SCRN_HEIGHT, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
	*/

	gluPerspective(70, scrnWidth / (float)scrnHeight, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, 70, 140, 0, 0, 0, 0, 1, 0);

	drawStage(-0.5, 0, -0.5);
	// eind lesley deel

	//drawStage(-0.5, 0, -0.5, 0, 0, 1);

	int j = 0;
	for (; j < spheres.size(); j++)
	{
		drawSphere(&spheres.at(j));

	}
}

void Game::drawSphere(const Sphere * sphere)
{
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
	glTexCoord2f(0, 1.0);	glVertex2f(0, SCRN_HEIGHT);
	glTexCoord2f(1.0, 1.0); glVertex2f(SCRN_WIDTH, SCRN_HEIGHT);
	glTexCoord2f(1.0, 0);	glVertex2f(SCRN_WIDTH, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Game::drawStage(GLfloat idx, GLfloat idy, GLfloat idz)
{
	// begin lesley deel
	glPushMatrix();
	glTranslatef(idx, idy, idz);
	glTranslatef(0.5f, -0.2f, 0.5f);

	glRotatef(pitch, 1, 0, 0);
	glRotatef(yaw, 0, 0, 1);
	glRotatef(ry, 0, 1, 0);

	glTranslatef(-0.5, 0.2f, -0.5);
	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	objm->draw();

	glPopMatrix();
	//models.push_back(pair<int, ObjModel*>(100, new ObjModel("models/maze/maze1.obj")));
	/*
	glBindTexture(GL_TEXTURE_2D, wood_texture.getTextureId());
*/
}

string Game::getVars()
{
	// begin lesley deel
	string video_state;
	if (video_on) video_state = "ON"; else video_state = "OFF";

	stringstream strs;
	strs << "VIDEO=" << video_state << " pitchX=" << pitch << " yawZ=" << yaw << endl;
	return strs.str();
	// eind lesley deel
}

bool Game::isRunning()
{
	return running;
}