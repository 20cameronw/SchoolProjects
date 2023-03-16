/*==================================================================================================
 PROGRAMMER:			Yang Wang
 COURSE:				CSC 525/625
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	XXX
 DESCRIPTION:			Demo: drawing points.
 NOTE:					N/A
 FILES:					points.cpp, (myCPPproj.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2019
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on myCPPproj.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <GL/glut.h>				// include GLUT library

//********* Prototypes **************************************************************
void myInit();
void myDisplayCallback();

void drawPoints();

//********* Subroutines *************************************************************
int main(int argc, char ** argv)
{glutInit(& argc, argv);					// initialization

 glutInitWindowSize(400, 400);				// specify a window size
 glutInitWindowPosition(100, 0);			// specify a window position
 glutCreateWindow("Simple Point Drawing");	// create a titled window

 myInit();									// specify some settings

 glutDisplayFunc(myDisplayCallback);		// register a callback

 glutMainLoop();							// get into an infinite loop

 return 1;									// something wrong happened
}

//***********************************************************************************
void drawPoints()
{glBegin(GL_POINTS);	// use the default point size: 1
   glColor3f(1, 0, 0);			// specify drawing color: red 
   glVertex2i(5, -5);			// specify a point location
   glVertex2i(-120, 70);		// 2nd point
   glVertex2i(100, 100);		// 3rd point
 glEnd();

 glPointSize(5);		// change point size to 5
 glColor3f(0, 0, 1);	// change drawing color to blue

 glBegin(GL_POINTS);
   glVertex2f(8.3, -9.7);
   glVertex2f(-106.8, 71.5);
   glColor3i(0, 1, 0);		// a common error !!! (when use an integral type for parameters) 
   glVertex2f(110.0, 105.5);
 glEnd();

 glPointSize(1);		// change point size back to 1
 
 glBegin(GL_POINTS);	// use points to form X-/Y-axes
   glColor3f(0, 0, 0);			 // change drawing color to black
   for (int x=-150; x<=150; x++) // draw X-axis
     glVertex2i(x, 0);
   for (int y=-150; y<=150; y++) // draw Y-axis
     glVertex2i(0, y);
 glEnd();
}

//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background clor: white 
 gluOrtho2D(-200, 200, -200, 200);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{glClear(GL_COLOR_BUFFER_BIT);	// draw the background

 drawPoints();

 glFlush(); // flush out the buffer contents
}