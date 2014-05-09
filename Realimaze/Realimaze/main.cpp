#include <glut.h>
#include <gl/GL.h>

float x = 10, y = 15, z = 10, rotation = 0;
int height, width;
bool up, down, left, right;

void DrawFrame();
void DrawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz);

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// PERSPECTIVE
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluPerspective(20, width / (float)height, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
			  0, 0, 0,
			  0, 1, 0);

	DrawCube(3, 0, 0, 1, 0, 0);
	DrawCube(0, 3, 0, 0, 1, 0);
	DrawCube(0, 0, 3, 0, 0, 1);

	// ORTHOGONAL
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glOrtho(0, width, 0, height, -1, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawFrame();

	glutSwapBuffers();
}

void DrawFrame()
{
	glBegin(GL_QUADS);
	glColor3f(255, 255, 255);
	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height / 20.0);
	glVertex2f(0, height / 20.0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(width / 20.0, 0);
	glVertex2f(width / 20.0, height);
	glVertex2f(0, height);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(width, height);
	glVertex2f(width*(19.0 / 20.0), height);
	glVertex2f(width*(19.0 / 20.0), 0);
	glVertex2f(width, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(width, height);
	glVertex2f(width, height*(19.0 / 20.0));
	glVertex2f(0, height*(19.0 / 20.0));
	glVertex2f(0, height);
	glEnd();
}

void DrawCube(GLfloat idx, GLfloat idy, GLfloat idz, GLfloat rx, GLfloat ry, GLfloat rz)
{
	glPushMatrix();
	glTranslatef(idx, idy, idz);
	glTranslatef(0.5f, 0.5f, 0.5f);
	glRotatef(rotation, rx, ry, rz);
	glTranslatef(-0.5, -0.5, -0.5);

	glBegin(GL_QUADS);
	glColor3f(255, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 255, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 255);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
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
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(255, 0, 255);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 0, 1);
	glEnd();
	glPopMatrix();
}

void Reshape(GLint newWidth, GLint newHeight)
{
	height = newHeight;
	width = newWidth;
	glViewport(0, 0, width, height);
}

void InitGraphics(void)
{
	glEnable(GL_DEPTH_TEST);
}

void MouseButton(int button, int state, int x, int y)
{
}

void MouseMotion(int x, int y)
{
}

void IdleFunc(void)
{
	rotation += 0.1f;
	glutPostRedisplay();
	if (up)
		y -= 0.01;
	if (down)
		y += 0.01;
	if (left)
		x -= 0.01;
	if (right)
		x += 0.01;
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		up = true;
		break;
	case 's':
		down = true;
		break;
	case 'a':
		left = true;
		break;
	case 'd':
		right = true;
		break;
	case 27:
		exit(0);
		break;
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		up = false;
		break;
	case 's':
		down = false;
		break;
	case 'a':
		left = false;
		break;
	case 'd':
		right = false;
		break;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("realimaze");

	// Initialize OpenGL graphics state
	InitGraphics();

	// Register callbacks:
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(IdleFunc);

	// Turn the flow of control over to GLUT
	glutMainLoop();
	return 0;
}