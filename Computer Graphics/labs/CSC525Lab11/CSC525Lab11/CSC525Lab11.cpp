/*=================================================================
COURSE: CSC 525 Lab 11
PROGRAMMERS: Venkatesh Pagadala, Ravi Teja Pilli, Cameron Weston, Vivek Kovi, Pranay Kalluri
LAST MODIFIED DATE: 10/29/2022
DESCRIPTION: Event driven programming using menus with OpenGL
FILES: Lab11.cpp
IDE/COMPILER: Microsoft Visual Studio 2019
INSTRUCTION FOR COMPILATION AND EXECUTION:
1. Double click on Lab007.sln (the solution file in my VS project) to OPEN the project
2. Press Ctrl+F7 to COMPILE
3. Press Ctrl+F5 to EXECUTE
=================================================================*/

#include <string>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;

//* Prototypes ********
void myInit();
void myDisplayCallback();
void drawMessage(string, int, int);
void drawAxis();
void keyboardCallback(unsigned char, int, int);
void mouse(int, int, int, int);
void mouseMotion(int, int);
void menuForFont(int);
void menuForColor(int);
void mainMenu(int);


void* font = GLUT_BITMAP_TIMES_ROMAN_24;
void* font2 = GLUT_BITMAP_HELVETICA_12;
void* currentFont = font;

string message = "";
bool firstTyped = false;
int rasterX;
int rasterY;
bool lButtonHeld = false;
bool rButtonHeld = false;
bool doneTyping = false;
int charCount = 0;
bool clickedAfterType = false;
int colorMenu;
int fontMenu;
int mainMenuId;
int window;
int colorNum;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(60, 0);
	window = glutCreateWindow("Lab 11");
	myInit();
	glutDisplayFunc(myDisplayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	
	colorMenu = glutCreateMenu(menuForColor);
	glutAddMenuEntry("Green", 10);
	glutAddMenuEntry("Blue", 11);
	fontMenu = glutCreateMenu(menuForFont);
	glutAddMenuEntry("Times New Roman 24", 20);
	glutAddMenuEntry("Helvetica 12", 21);

	mainMenuId = glutCreateMenu(mainMenu);
	glutAddSubMenu("Colors", colorMenu);
	glutAddSubMenu("Fonts", fontMenu);
	glutAddMenuEntry("Exit", 0);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

	return 1;
}

void drawAxis()
{
	glPointSize(1);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	for (int x = -150; x <= 150; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y = -150; y <= 150; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();

	glRasterPos2i(152, 0);
	glutBitmapCharacter(font, 'x');
	glRasterPos2i(0, 152);
	glutBitmapCharacter(font, 'y');

}

void keyboardCallback(unsigned char key, int x, int y)
{
	if (!firstTyped)
	{
		rasterX = x;
		rasterY = y;
		firstTyped = true;
	}
	if (!doneTyping)
	{
		message += key;
		drawMessage(message, rasterX - 200, 200 - rasterY);
		charCount++;
	}
	if (charCount >= 30 || clickedAfterType)
		doneTyping = true;
}

void mouse(int buttonName, int state, int x, int y)
{
	if (firstTyped)
		clickedAfterType = true;

	if (buttonName == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		rButtonHeld = true;
		myDisplayCallback();
		drawMessage(message, rasterX - 200, 200 - rasterY);
	}

	if (buttonName == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		lButtonHeld = true;
		myDisplayCallback();
		drawMessage(message, rasterX - 200, 200 - rasterY);
	}


	if (buttonName == GLUT_LEFT_BUTTON && state == GLUT_UP)
		lButtonHeld = false;

	if (buttonName == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		rButtonHeld = false;

	glFlush();

}

void menuForColor(int val)
{
	colorNum = val;
	myDisplayCallback();
	drawMessage(message, rasterX - 200, 200 - rasterY);
}

void mainMenu(int val)
{
	if (val == 0)
	{
		glutDestroyWindow(window);
		exit(0);
	}
}

void mouseMotion(int x, int y)
{
	if (rButtonHeld)
	{
		myDisplayCallback();
		drawMessage(message, x - 200, 200 - y);
	}
	else if (lButtonHeld)
	{
		myDisplayCallback();
		drawMessage(message, x - 200, 200 - y);
	}
	glFlush();
}

void menuForFont(int val)
{
	switch (val)
	{
		case 20:
			currentFont = font;
			break;
		case 21:
			currentFont = font2;
			break;
	}
	myDisplayCallback();
	drawMessage(message, rasterX - 200, 200 - rasterY);
}

void drawMessage(string text, int x, int y)
{
	switch (colorNum)
	{
		case 10:
			glColor3f(0, .9, 0);
			break;
		case 11:
			glColor3f(0, .2, .8);
			break;
		default:
			glColor3f(0, 0, 0);
			break;
	}
		
	glRasterPos2f(x, y);
	for (int i = 0; i < text.length(); i++)
	{
		glutBitmapCharacter(currentFont, text[i]);
	}
	glFlush();
}

void myInit()
{
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(-200, 200, -200, 200);
}

void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawAxis();

	glFlush();
}