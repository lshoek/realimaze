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
Texture text{ "resources/classicfnt32.png" };

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
	glEnable(GL_DEPTH_TEST); //Instead of glutInit
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
	testGame.update();
	glutPostRedisplay();
}

void Manager::draw(void)
{
	if (testGame.isRunning())
		testGame.draw();

	//Orthogonal
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glOrtho(0, SCRN_WIDTH, 0, SCRN_HEIGHT, -1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Text
	GLuint txtr = text.getTextureId();
	glBindTexture(GL_TEXTURE_2D, txtr);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glTranslatef(SCRN_WIDTH/2, SCRN_HEIGHT/2, 0);
	glColor4f(0, 0, 0, 1);
	glListBase(char_list);
	glPushMatrix();
	glCallLists(11, GL_UNSIGNED_BYTE, "Hello World");
	glPopMatrix();
	glTranslatef(2, 2, 0);
	glColor4f(1, 1, 1, 1);
	glCallLists(11, GL_UNSIGNED_BYTE, "Hello World");

	glutSwapBuffers();
}

void Manager::kDown(unsigned char key, int x, int y)
{}

void Manager::kUp(unsigned char key, int x, int y)
{}
