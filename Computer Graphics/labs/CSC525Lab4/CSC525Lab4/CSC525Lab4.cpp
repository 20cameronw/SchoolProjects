/*================================================================================================= =
PROGRAMMER:	Cameron Weston, Ravi Teja Pilli, Vivek Kovi, Venkatesh Pagadala, Pranay Kalluri
COURSE : CSC 525 / 625
LAST MODIFIED DATE : 9 / 17 / 2022
DESCRIPTION : Lab 4 - Drawing polygons using GL_FILL, GL_LINE, GL_POINT, GL_POLYGON_STIPPLE
FILES : CSC525Lab4.cpp
IDE / COMPILER : MicroSoft Visual Studio 2019
==================================================================================================*/
#include <iostream>
#include <math.h>
#include <GL/glut.h>				


//********* Prototypes **************************************************************
void myInit();
void myDisplayCallback();
void display(void);

void drawPoints();

//********* 32x32 bitmap pattern ****************************************************
GLubyte aPattern[] = {
	0x00, 0x00, 0x00, 0x00, //line 1 
	0x00, 0x00, 0x00, 0x00, //line 2
	0x00, 0x00, 0x00, 0x00, //line 3
	0x00, 0x00, 0x00, 0x00, //line 4
	0x00, 0x00, 0x00, 0x00, //line 5
	0x00, 0x00, 0x00, 0x00, //line 6
	0x00, 0x00, 0x00, 0x00, //line 7
	0x00, 0x00, 0x00, 0x00, //line 8

	0x00, 0x00, 0x00, 0x00, //line 9
	0x00, 0x00, 0x00, 0x00, //line 10
	0x00, 0xF0, 0x0F, 0x00, //line 11
	0x00, 0xF0, 0x0F, 0x00, //line 12
	0x00, 0xFF, 0xFF, 0x00, //line 13
	0x00, 0xFF, 0xFF, 0x00, //line 14
	0x00, 0xFF, 0xFF, 0x00, //line 15
	0x00, 0xFF, 0xFF, 0x00, //line 16

	0x00, 0x0F, 0xF0, 0x00, //line 17
	0x00, 0x0F, 0xF0, 0x00, //line 18
	0x00, 0x0F, 0xF0, 0x00, //line 19
	0x00, 0x0F, 0xF0, 0x00, //line 20
	0x03, 0xF0, 0x0F, 0xC0, //line 21
	0x03, 0xF0, 0x0F, 0xC0, //line 22
	0x03, 0xF0, 0x0F, 0xC0, //line 23
	0x03, 0xF0, 0x0F, 0xC0, //line 24

	0x03, 0xF0, 0x0F, 0xC0, //line 25
	0x03, 0xF0, 0x0F, 0xC0, //line 26
	0x00, 0x00, 0x00, 0x00, //line 27
	0x00, 0x00, 0x00, 0x00, //line 28
	0x00, 0x00, 0x00, 0x00, //line 29
	0x00, 0x00, 0x00, 0x00, //line 30
	0x00, 0x00, 0x00, 0x00, //line 31
	0x00, 0x00, 0x00, 0x00  //line 32
};

int displayMode = 0;

//********* Subroutines *************************************************************
int main(int argc, char** argv)
{
	glutInit(&argc, argv);					// initialization

	glutInitWindowSize(400, 400);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Lab 4: Polygons");	// create a titled window

	myInit();								// specify some settings

	glutDisplayFunc(myDisplayCallback);		// register a callback

	//prompt the user to select a display mode 
	std::cout << "Select a display mode:\n (1) GL_FILL\n (2) GL_LINE\n (3) GL_POINT\n (4) FILL WITH A PATTERN\n";
	std::cin >> displayMode;
	if (displayMode < 0 || displayMode > 4)
	{
		std::cout << "ERROR: Invalid input\n";
		return 1;
	}

	glutMainLoop();							// get into an infinite loop

	return 1;									// something wrong happened
}

//***********************************************************************************
void drawPoints()
{
	glPointSize(1);
	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	for (int x = -150; x <= 150; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y = -150; y <= 150; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();

	switch (displayMode)
	{
		case 1:			// if the case is 1 then the default is already GL_FILL
			break; 
		case 2:
			glPolygonMode(GL_FRONT, GL_LINE);
			glLineWidth(5);
			break;
		case 3:
			glPolygonMode(GL_FRONT, GL_POINT);
			glPointSize(5);
			break;
		case 4:
			glEnable(GL_POLYGON_STIPPLE);
			glPolygonStipple(aPattern);
			break;
	}
	glBegin(GL_POLYGON);
		glColor3f(0.4, 0.8, 0.4);
		glVertex2i(0, 80);
		glColor3f(0.7, 0.5, 0.45);
		glVertex2i(-70, 0);
		glColor3f(0, 0.7, 0.7);
		glVertex2i(-30, -60);
		glColor3f(0.4, 0, 0.4);
		glVertex2i(30, -60);
		glColor3f(0, 1, .4);
		glVertex2i(70, 0);
	glEnd();
	//check if the GL_POLYGON_STIPPLE capability is enabled and disable it
	if (glIsEnabled(GL_POLYGON_STIPPLE)) glDisable(GL_POLYGON_STIPPLE);
}

//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-200, 200, -200, 200);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawPoints();
	display();

	glFlush(); // flush out the buffer contents
}

void display(void)
{
	GLfloat white[3] = { 1.0, 1.0, 1.0 };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3fv(white);
	glRasterPos2i(20, 60);
	printString(“THE QUICK BROWN FOX JUMPS”);
	glRasterPos2i(20, 40);
	printString(“OVER A LAZY DOG”);
	glFlush();
}
