#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <GL/glut.h>				// include GLUT library

using namespace std;

//********* Prototypes **************************************************************
void myInit();
void myDisplayCallback();

void drawPoints();

struct Point
{
    int x;
    int y;
};

Point points[50] = { 0 };
int numberPoints = 0;

//********* Subroutines *************************************************************
int main(int argc, char** argv)
{
    glutInit(&argc, argv);					// initialization

    glutInitWindowSize(400, 400);				// specify a window size
    glutInitWindowPosition(100, 0);			// specify a window position
    glutCreateWindow("Simple Point Drawing");	// create a titled window

    myInit();								// specify some settings

    glutDisplayFunc(myDisplayCallback);		// register a callback

    // get input file name from the user and read its contents
    cout << "Please enter a file name" << endl;
    string fileLocation = "C:\\temp\\";
    string fileName;
    fstream myFile;
    cin >> fileName;
    myFile.open(fileLocation + fileName);
    string line;
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            istringstream sline(line);
            int number;
            sline >> number;
            points[numberPoints].x = number;
            sline >> number;
            points[numberPoints].y = number;
            numberPoints++;
        }
        myFile.close();
        cout << "Read Points: " << endl;

        for (int i = 0; i < numberPoints; i++)
        {
            cout << points[i].x << ", " << points[i].y << endl;
        }
    }
    else
    {
        std::cout << "ERROR: Could not open file.";
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


    glColor3f(.2, .4, .6);
    for (int i = 0; i < numberPoints - 1; i++)
    {
        //load current points to draw
        int x1 = points[i].x;
        int y1 = points[i].y;
        int x2 = points[i + 1].x;
        int y2 = points[i + 1].y;
        
        cout << "Loaded Points " << x1 << ", " << y1
            << ", " << x2 << ", " << y2 << endl;
        

        if (x1 == x2 && y1 == y2)
        {
            continue;
        }
        else if (x1 == x2)
        {
            glBegin(GL_POINTS);
            //draw vertical line
            for (int y = y1; y < y2; y++)
            {
                glVertex2i(x1, y);
            }
            glEnd();
        }
        else if (y1 == y2)
        {
            glBegin(GL_POINTS);
            //draw horizontal line
            for (int x = x1; x < x2; x++)
            {
                glVertex2i(x, y1);
            }
            glEnd();
        }
        else if (x1 != x2 && y1 != y2)
        {
            //draw diagonal line
            float slope = (y2 - y1) / (x2 - x1);
            int hypotenuse = sqrt((x1 * x1) + (y1 * y1));
            if (abs(slope) <= 1)
            {
                glBegin(GL_POINTS);
                for (int x = x1; x < hypotenuse; x++)
                {
                    int y = (i - x1) * slope + y1;
                    glVertex2i(x, y);
                }
                glEnd();
            }
            else if (abs(slope) > 1)
            {
                glBegin(GL_POINTS);
                for (int y = y1; y < hypotenuse; y++)
                {
                    int x = (y - y1) * (1 / slope) + x1;

                    glVertex2i(x, y);
                }
                glEnd();
            }

        }
    }

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

    glFlush(); // flush out the buffer contents
}