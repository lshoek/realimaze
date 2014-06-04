#include <string>
#include <iostream>
#include <vector>
#include <glut.h>
#include "Manager.h"
#include "Game.h"
#include "Font.h"
using namespace std;

Manager* mngr = NULL;
GLuint char_list;
Texture text_texture{ "resources/classicfnt32.png" };
bool key_up, key_down, key_left, key_right;
int lastUpdateTime;

void idleFunc()
{ mngr->update(); }

void displayFunc()
{ mngr->draw(); }

void keyDown(unsigned char key, int x, int y)
{ mngr->kDown(key, x, y); }

void keyUp(unsigned char key, int x, int y)
{ mngr->kUp(key, x, y); }

//Instance of a game. Every game launches a menu first. Stages can be selected from this menu. The menu is left out for the time being.
Manager::Manager()
{
	mngr = this;
	glutInitWindowSize(SCRN_WIDTH, SCRN_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Realimaze");

	//Construct displaylists
	Font font{ "resources/classicfnt32.fnt" };
	char_list = glGenLists(256);
	for (int i = 0; i < 256; i++)
	{
		if (font.charmap.find(i) == font.charmap.end())
			continue;
		Glyph &g = font.charmap[i];
		float cx = g.x / 128.0f;
		float cy = g.y / 128.0f;
		float sizex = g.width / 128.0f;
		float sizey = g.height / 128.0f;

		glNewList(char_list + i, GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(cx, cy);				glVertex2d(0, g.height);
		glTexCoord2f(cx, cy+sizey);			glVertex2d(0, 0);
		glTexCoord2f(cx+sizex, cy+sizey);	glVertex2d(g.width, 0);
		glTexCoord2f(cx+sizex, cy);			glVertex2d(g.width, g.height);
		glEnd();
		glTranslatef(g.xadvance, 0, 0);
		glEndList();
	}

	//Register callbacks
	glutIdleFunc(&idleFunc);
	glutDisplayFunc(&displayFunc);
	glutKeyboardFunc(&keyDown);
	glutKeyboardUpFunc(&keyUp);
	testGame.launchGame();
	glutMainLoop();
}

Manager::~Manager()
{}

void Manager::update(void)
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	testGame.update((time - lastUpdateTime) / 1000.0);
	lastUpdateTime = time;

	if (key_up)
		testGame.rotateYaw(-1.0);
	if (key_down)
		testGame.rotateYaw(1.0);
	if (key_left)
		testGame.rotatePitch(1.0);
	if (key_right)
		testGame.rotatePitch(-1.0);

	glutPostRedisplay();
}

void Manager::draw(void)
{
	if (testGame.isRunning())
		testGame.draw();

	//Orthogonal (additional text)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glOrtho(0, SCRN_WIDTH, 0, SCRN_HEIGHT, -1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawText("realimaze v0.1 augmented reality project", 10, 20, 1.5);
	//drawText(testGame.getVars(), 10, 10, 1);

	glutSwapBuffers();
}

void Manager::drawText(const string text, const GLfloat x, const GLfloat y, const float scale)
{
	glBindTexture(GL_TEXTURE_2D, text_texture.getTextureId());
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(scale, scale, 1);
	glColor4f(0, 0, 0, 1);
	glListBase(char_list);
	glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x+1, y+1, 0);
	glScalef(scale, scale, 1);
	glColor4f(1, 1, 1, 1);
	glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Manager::kDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		key_up = true;
		break;
	case 's':
		key_down = true;
		break;
	case 'a':
		key_left = true;
		break;
	case 'd':
		key_right = true;
		break;
	case 27:
		exit(0);
		break;
	}
}

void Manager::kUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		key_up = false;
		break;
	case 's':
		key_down = false;
		break;
	case 'a':
		key_left = false;
		break;
	case 'd':
		key_right = false;
		break;
	case 27:
		exit(0);
		break;
	}
}