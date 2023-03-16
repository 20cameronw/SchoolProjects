/*=================================================================
COURSE: CSC 525/625, assignment 07
PROGRAMMERS: Venkatesh Pagadala, Ravi Teja Pilli, Cameron Weston, Vivek Kovi, Pranay Kalluri
LAST MODIFIED DATE: 10/8/2022
DESCRIPTION: This program is to show the head scratching man bitmap
FILES: Lab007.cpp
IDE/COMPILER: Microsoft Visual Studio 2019
INSTRUCTION FOR COMPILATION AND EXECUTION:
1. Double click on Lab007.sln (the solution file in my VS project) to OPEN the project
2. Press Ctrl+F7 to COMPILE
3. Press Ctrl+F5 to EXECUTE
=================================================================*/
#include <iostream>
#include <string>
#include <sstream>
#include <GL/glut.h> // include GLUT library last

using namespace std;

//global constants
const int windowWidth = 400;
const int windowHeight = 400;
void* font = GLUT_BITMAP_TIMES_ROMAN_24;
const GLfloat threepipe[6][3] = {
	{60,  55, 40},
	{60, -50, 40},
	{65,  90, -70},
	{65,   0, -70},
	{-70,  70, 20},
	{-70, -20, 20}
};
int pipeRotationState[3] = { 0 };
enum menuOption
{
	plusX,
	plusY, 
	plusZ, 
	minusX,
	minusY,
	minusZ,
	reset,
	exitWindow
};


//prototypes
void drawPipe();
void drawAxis();
void init();
void menuInit();
void menuListener(int);
void display();

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(windowWidth, windowHeight);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("OpenGL Projections");	// create a titled window

	init();

	glutMainLoop();							// get into an infinite loop
}



void drawPipe()
{
	glPushMatrix();

	glRotated(pipeRotationState[0], 1, 0, 0);
	glRotated(pipeRotationState[1], 0, 1, 0);
	glRotated(pipeRotationState[2], 0, 0, 1);

	glFrontFace(GL_CW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);


	glBegin(GL_POLYGON);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(threepipe[2][0], threepipe[2][1], threepipe[2][2]);
		glVertex3f(threepipe[4][0], threepipe[4][1], threepipe[4][2]);
		glVertex3f(threepipe[5][0], threepipe[5][1], threepipe[5][2]);
		glVertex3f(threepipe[3][0], threepipe[3][1], threepipe[3][2]);
	glEnd();


	glBegin(GL_POLYGON);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(threepipe[4][0], threepipe[4][1], threepipe[4][2]);
		glVertex3f(threepipe[0][0], threepipe[0][1], threepipe[0][2]);
		glVertex3f(threepipe[1][0], threepipe[1][1], threepipe[1][2]);
		glVertex3f(threepipe[5][0], threepipe[5][1], threepipe[5][2]);
	glEnd();
	
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(threepipe[0][0], threepipe[0][1], threepipe[0][2]);
		glVertex3f(threepipe[2][0], threepipe[2][1], threepipe[2][2]);
		glVertex3f(threepipe[3][0], threepipe[3][1], threepipe[3][2]);
		glVertex3f(threepipe[1][0], threepipe[1][1], threepipe[1][2]);
	glEnd();

	glPopMatrix();
}


void drawAxis() 
{
	glPointSize(1);		// change point size back to 1

	glBegin(GL_POINTS);	// use points to form X-/Y-axes

		glColor3f(0, 0, 0);	// change drawing color to black

		for (int x = -150; x <= 150; x++) // draw X-axis
			glVertex3i(x, 0, 0);

		for (int y = -150; y <= 150; y++) // draw Y-axis
			glVertex3i(0, y, 0);

		for (int z = -150; z <= 150; z++) // draw Z-axis
			glVertex3i(0, 0, z);

	glEnd();

	//label the axis
	glRasterPos3i(152, 0, 5);
	glutBitmapCharacter(font, 'x');

	glRasterPos3i(0, 152, 5);
	glutBitmapCharacter(font, 'y');

}


void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1, 1, 1, 0);
	glOrtho(-200, 200, -200, 200, -200, 200);  
	gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);
	menuInit();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAxis();
	drawPipe();

	glFlush();
	glutSwapBuffers();
}


void menuListener(int value)
{
	switch (value)
	{
		case plusX:
			pipeRotationState[0] += 45;
			break;
		case plusY:
			pipeRotationState[1] += 45;
			break;
		case plusZ:
			pipeRotationState[2] += 45;
			break;
		case minusX:
			pipeRotationState[0] -= 45;
			break;
		case minusY:
			pipeRotationState[1] -= 45;
			break;
		case minusZ:
			pipeRotationState[2] -= 45;
			break;
		case reset:
			pipeRotationState[0] = 0;
			pipeRotationState[1] = 0;
			pipeRotationState[2] = 0;
			break;
		case exitWindow:
			exit(0);
			break;
	}
	display();
}

void menuInit() 
{
	int rotateSubmenu;
	rotateSubmenu = glutCreateMenu(menuListener);
	glutAddMenuEntry("x + 45", plusX);
	glutAddMenuEntry("x - 45", minusX);
	glutAddMenuEntry("y + 45", plusY);
	glutAddMenuEntry("y - 45", minusY);
	glutAddMenuEntry("z + 45", plusZ);
	glutAddMenuEntry("z - 45", minusZ);

	glutCreateMenu(menuListener);
	glutAddSubMenu("Rotate", rotateSubmenu);
	glutAddMenuEntry("Reset", reset);
	glutAddMenuEntry("Exit", exitWindow);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

