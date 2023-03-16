/*================================================================================================= =
PROGRAMMER:	Cameron Weston, Ravi Teja Pilli, Vivek Kovi, Venkatesh Pagadala, Pranay Kalluri
COURSE : CSC 525 / 625
LAST MODIFIED DATE : 9 / 24 / 2022
DESCRIPTION : Rastering text with glut
FILES : CSC525Lab5.cpp
IDE / COMPILER : MicroSoft Visual Studio 2019
==================================================================================================*/
#include <string>
#include <iostream>
#include <GL/glut.h>

using namespace std;

//* Prototypes ********
void myInit();
void myDisplayCallback();
void drawMessage(float x, float y);
void drawPoints();

void* font = GLUT_BITMAP_TIMES_ROMAN_24;

string message = "";
//* Subroutines *******
int main(int argc, char** argv)
{
	glutInit(&argc, argv);					// initialization
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);				// specify a window size
	glutInitWindowPosition(60, 0);			// specify a window position
	glutCreateWindow("Lab 4: User TEXT");	// create a titled window

	myInit();								// specify some settings

	glutDisplayFunc(myDisplayCallback);		// register a callback

	//prompt the user to select a display mode

	cout << "Enter the message : " << endl;
	getline(cin, message);
	
	glutMainLoop();							// get into an infinite loop

	return 1;									// something wrong happened
}

//***********
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
	
	glRasterPos2i(152, 0);
	glutBitmapCharacter(font, 'x');

	glRasterPos2i(0, 152);
	glutBitmapCharacter(font, 'y');

	drawMessage(-100, 20);

}

void drawMessage(float x, float y)
{
	glColor3f(.2, .4, .6);
	glRasterPos2f(x, y);
	for (int i = 0; i < message.length(); i++)
	{
		glutBitmapCharacter(font, message[i]);
	}
}

//***********
void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white
	gluOrtho2D(-200, 200, -200, 200);  // specify a viewing area
}

//***********
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawPoints();

	glFlush(); // flush out the buffer contents
}