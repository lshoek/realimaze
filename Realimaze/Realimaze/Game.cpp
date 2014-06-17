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
#include <thread>
#include <windows.h>
#include "Engine.h"

using namespace std;

void timerTick(void);
GLfloat x = 10, y = 5, z = 1, rotation = 0;

int scrnWidth, scrnHeight;
bool running = false;
void openCV(void);

ObjModel* objm;

Game::Game(int w, int h)
{
	scrnWidth = w;
	scrnHeight = h;

	//objm = new ObjModel("models/holes/mazeWithHoles.obj"); 
	objm = new ObjModel("models/Normalmaze.obj");

	//LIGHTING
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	GLfloat LightPosition[] = { 10.0f, 10.0f, 10.0f, 1.0f };
	GLfloat LightAmbient[] = { 0, 0, 0, 1.0f };
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);

	GLfloat LightModelAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat MaterialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat MaterialEmission[] = { 0, 0, 0, 1.0f };
	glLightModelfv(GL_AMBIENT, LightModelAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MaterialSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, MaterialEmission);
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

void Game::update(float tfac)
{
	yaw = orientation.getOrientationFactor().xPos * MAX_ROTATION; // left to right
	pitch = orientation.getOrientationFactor().yPos * MAX_ROTATION; // top to bottom
	cout << "The amount of yaw is: " << yaw << " The amount of pitch is: " << pitch << endl;
	glutPostRedisplay();

	engine.Step(orientation.getOrientationFactor().xPos, orientation.getOrientationFactor().yPos);

	int time = glutGet(GLUT_ELAPSED_TIME);
	timeFac = (time - lastFrameTime) / 1000.0;
	lastFrameTime = time;
	rotation+=0.05;
}

void Game::draw(const vector<Sphere> spheres)
{
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, SCRN_WIDTH_FULL, SCRN_HEIGHT_FULL);
	glClearColor(0.6f, 0.6f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (video_on)
	{
		//ORTHOGONAL
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glOrtho(0, SCRN_WIDTH_FULL, 0, SCRN_HEIGHT_FULL, -1, 200);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		displayImage();
	}
	// PERSPECTIVE
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, scrnWidth / (float)scrnHeight, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, 80, 140, 0, 0, 0, 0, 1, 0);
	drawStage(0, 10.0, 0, spheres);
	glDisable(GL_LIGHTING);
}

void Game::drawSphere(const Sphere * sphere)
{
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(sphere->position.x, 5, sphere->position.y);
	glutSolidSphere(sphere->radius, 50 ,50);
	glPopMatrix();
}

void Game::openCV(void)
{
	while (true)
	{
		displayImage();
	}
}

void Game::displayImage()
{
	waitKey(1000);
	orientation.modifyImage();
	Texture img{ orientation.getVideoImage() };
	glBindTexture(GL_TEXTURE_2D, img.getTextureId());
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(0, 0);
	glTexCoord2f(0, 1.0);	glVertex2f(0, SCRN_HEIGHT_FULL);
	glTexCoord2f(1.0, 1.0); glVertex2f(SCRN_WIDTH_FULL, SCRN_HEIGHT_FULL);
	glTexCoord2f(1.0, 0);	glVertex2f(SCRN_WIDTH_FULL, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	orientation.releaseImageData();
}

void Game::drawStage(GLfloat idx, GLfloat idy, GLfloat idz,const vector<Sphere> spheres)
{
	glPushMatrix();
	glTranslatef(idx, idy, idz);

	glRotatef(pitch+60, 1, 0, 0);
	glRotatef(yaw, 0, 0, 1);

	glTranslatef(-1*idx, -1*idy, -1*idz);
	glScalef(1.3, 1.3, 1.3);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	objm->draw();

	glDisable(GL_TEXTURE_2D);

	int j = 0;
	for (; j < spheres.size(); j++)
		drawSphere(&spheres[j]);

	glPopMatrix();
}

string Game::getVars()
{
	string video_state;
	if (video_on) video_state = "ON"; else video_state = "OFF";

	stringstream strs;
	strs << "VIDEO=" << video_state << " pitchX=" << pitch << " yawZ=" << yaw << endl;
	return strs.str();
}

bool Game::isRunning()
{
	return running;
}
