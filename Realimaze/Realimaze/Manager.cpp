#include <string>
#include <iostream>
#include <vector>
#include <glut.h>
#include <Windows.h>
#include <time.h>
#include <thread>

#include "Manager.h"
#include "Game.h"
#include "Font.h"
#include "Vector2D.h"

using namespace std;

void keyHandling(void);
void timerTick(void);

Manager* mngr = NULL;
GLuint char_list;
Texture text_texture{ "resources/classicfnt32.png" };

bool key_up, key_down, key_left, key_right, key_back, key_front, key_space;

int lastUpdateTime;

bool keys[256];
thread keyThread(keyHandling);
thread timer(timerTick);
float timerTime = 0;

/*Bas
ingame timer
*/
void timerTick(void)
{	
	while (true)
	{
		clock_t t;
		while (mngr == nullptr)
		{
		}
		if (mngr->engine.state == 0)
			timerTime = 0;
		while (mngr->engine.state == 0)
		{
			t = clock();
			Sleep(1);
			t = clock() - t;
			timerTime += ((float) t) / CLOCKS_PER_SEC;
		}
		Sleep(50);
	}
}

void keyHandling(void)
{
	while (true)
	{
		if (keys[27])//esc
		{
			mngr->testGame.~Game();
			mngr -> ~Manager();		
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
	// begin lesley deel
	mngr = this;

	cout << "first" << endl;
	glutInitWindowSize(SCRN_WIDTH_FULL, SCRN_HEIGHT_FULL);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//SetWindowPos(HWND_TOPMOST, HWND_TOPMOST, 0, 0, 1280, 960, SWP_SHOWWINDOW);
	glutCreateWindow("Realimaze");

	cout << "second" << endl;

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
	cout << "third" << endl;

	engine.addSphere(0, 0, 3, &engine.spheres);
	//engine.addLine(0, 40, 80, 0);
	//test over
	glEnable(GL_DEPTH_TEST); //Instead of glutInit

	cout << "fourth" << endl;
	
	//Register callbacks
	glutIdleFunc(&idleFunc);
	glutDisplayFunc(&displayFunc);
	glutKeyboardFunc(&keyDown);
	glutKeyboardUpFunc(&keyUp);
	testGame.launchGame();
	glutMainLoop();
	// eind lesley deel

	cout << "fifth" << endl;
}

/*
Made by Bas
*/
Manager::~Manager()
{	
	keyThread.join();
	timer.join();
	delete mngr;
}

void Manager::update(void)
{
	// begin lesley deel
	int time = glutGet(GLUT_ELAPSED_TIME);
	testGame.update((time - lastUpdateTime) / 1000.0);
	lastUpdateTime = time;

	if (key_up)
		testGame.orientation.orientPos.yPos += 0.1;
	if (key_down)
		testGame.orientation.orientPos.yPos -= 0.1;
	if (key_left)
		testGame.orientation.orientPos.xPos -= 0.1;
	if (key_right)
		testGame.orientation.orientPos.xPos += 0.1;
	if (key_space)
		testGame.orientation.centerPos = testGame.orientation.orientPos; //calibrate
	glutPostRedisplay();
	// eind lesley deel

}

void Manager::draw(void)
{
	// begin lesley deel
	if (testGame.isRunning())
	{
		//testGame.draw();
		testGame.draw(engine.spheres);
	}

	// ORTHOGONAL
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glOrtho(0, SCRN_WIDTH_FULL, 0, SCRN_HEIGHT_FULL, -1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawText("x", testGame.orientation.centerPos.xPos, testGame.orientation.centerPos.yPos, 2);
	drawText("x", testGame.orientation.orientPos.xPos, testGame.orientation.orientPos.yPos, 1);
	drawText("realimaze v0.1 augmented reality project", 10, 20, 1.5);
	drawText(testGame.getVars(), 10, 10, 1);
	glutSwapBuffers();
	// eind lesley deel
}

void Manager::drawText(const string text, const GLfloat x, const GLfloat y, const float scale)
{
	// begin lesley deel
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
	// eind lesley deel
}

void Manager::kDown(unsigned char key, int x, int y)
{
	// begin lesley deel
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
	case 32:
		key_space = true;
	case 'f':
		key_front = true;
		break;
	case 'r':
		key_back = true;
		break;
	case 27:
		exit(0);
		break;
	case 'x':
		testGame.video_on = !testGame.video_on;
		break;
	}
	// eind lesley deel
	keys[key] = true;
}

void Manager::kUp(unsigned char key, int x, int y)
{
	// begin lesley deel
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
	case 32:
		key_space = false;
	case 'f':
		key_front = false;
		break;
	case 'r':
		key_back = false;
		break;
	case 27:
		exit(0);
		break;
	}
	// eind lesley deel
	keys[key] = false;
}
