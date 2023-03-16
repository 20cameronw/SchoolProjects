/*-----------------------------------------------------------------------------------------
 COURSE:                CSC 525: Project 2
 PROGRAMMERS: Venkatesh Pagadala (20%), Ravi Teja Pilli(20%), Cameron Weston(20%), Vivek kovi(20%), pranay kalluri (20%)
 Last MODIFIED:            11/13/2022
 DESCRIPTION:           This is a basic text editing program that supports multiple fonts,
						colors, and sizes of text. The program uses OpenGL.
						Features include:
						1) Minimum 30 characters per row and 30 rows
						2) User specified color of to-be-entered text (minimum 3 colors)
						3) User specified font of to-be-entered text (minimum 3 fonts)
						4) Starting positioning of cursor
						5) Automatic text break into new line when max row space exceeded
						6) Enter key moves display position to beginning of the next row
						7) Backspace key erases previously typed character(s)
						8) User can save all current text in flat text format in a file
						  defined as C:\Temp\typed.txt
						9) User can terminate the program from menu option
 FILES: Project2.cpp
 IDE/COMPILER: Microsoft Visual Studio 2019
 INSTRUCTION FOR COMPILATION AND EXECUTION:
 1. Double click on Project2.sln (the solution file in my VS project) to OPEN the project
 2. Press Ctrl+F7 to COMPILE
 3. Press Ctrl+F5 to EXECUTE
-----------------------------------------------------------------------------------------*/

#include <vector>
#include <fstream>
#include <iostream>
#include <gl/glut.h>


//prototypes
void initEditorWindow();
void initInfoWindow();
void initMenu();
void editorDisplayCallback();
void infoDisplayCallback();
void menuHandler(int);
void mouseCallback(int, int, int, int);
void keyboardCallback(unsigned char, int, int);
void setStartPos(int);
void saveContent();
void drawText();
void drawLines();
int findLine(int);


//globals
int editorWindow;
int infoWindow;
void* currentFont = GLUT_BITMAP_TIMES_ROMAN_10;
float textColor[3] = { 0 };
std::vector<unsigned char> charList;
std::vector<void*> fontPerChar;
bool hasTyped = false;
int rasterStartX = -270;
int rasterStartY = 282;
int startLine = 1;
int windowWidth;
int windowHeight;


enum Menu_Option {
	save_content,
	glut_black,
	glut_red,
	glut_green,
	glut_blue,
	glut_8_BY_13,
	glut_9_BY_15,
	glut_TIMES_ROMAN_10,
	glut_TIMES_ROMAN_24,
	glut_HELVETICA_10,
	glut_HELVETICA_12,
	glut_HELVETICA_18,
	show_info,
	hide_info,
	exit_program
};

int main(int argc, char** argv)
{
	//init glut settings
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//init editor window
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(60, 50);
	editorWindow = glutCreateWindow("Text editor");
	initEditorWindow();


	//init info window
	glutInitWindowSize(600, 250);
	glutInitWindowPosition(700, 50);
	infoWindow = glutCreateWindow("Info");
	initInfoWindow();


	//enter infinite loop
	glutMainLoop();
	return 0;
}

void infowindow() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glRasterPos2d(-190, 165);
	char msg1[] = "INFO WINDOW !";
	for (int i = 0; i < strlen(msg1); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg1[i]);


	glRasterPos2d(-190, 135);
	char msg2[] = "This text editor allows you to type text on any line .";
	for (int i = 0; i < strlen(msg2); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);

	glRasterPos2d(-190, 105);
	char msg3[] = "user should press mouse right button ,";
	for (int i = 0; i < strlen(msg3); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);

	glRasterPos2d(-190, 75);
	char msg4[] = "to select fonts and colors from the menu.";
	for (int i = 0; i < strlen(msg4); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg4[i]);

	glRasterPos2d(-190, 35);
	char msg7[] = "You can erase a character by pressing the backspace key,  ";
	for (int i = 0; i < strlen(msg7); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg7[i]);

	glRasterPos2d(-190, 5);
	char msg8[] = "and you can go to a new line by pressing enter. ";
	for (int i = 0; i < strlen(msg8); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg8[i]);

	glRasterPos2d(-190, -35);
	char msg5[] = "you have option to save the text into local file . ";
	for (int i = 0; i < strlen(msg5); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg5[i]);

	glRasterPos2d(-190, -75);
	char msg6[] = "select EXIT from the menu to terminate the program.";
	for (int i = 0; i < strlen(msg6); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg6[i]);


}

void initEditorWindow()
{
	glClearColor(1, 1, 1, 0); //background color: white
	gluOrtho2D(-300, 300, -300, 300); //viewing area
	glutDisplayFunc(editorDisplayCallback); //register display callback
	initMenu();
	glutMouseFunc(mouseCallback);
	glutKeyboardFunc(keyboardCallback);
}

void initInfoWindow()
{
	glClearColor(1, 1, 1, 0); //background color: white
	gluOrtho2D(-200, 200, -200, 200); //viewing area
	glutDisplayFunc(infoDisplayCallback); //register display callback
	initMenu();
}

//display callback function for the editor window
void editorDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawLines();
	drawText();

	glFlush();
}

//display callback function for the info window
void infoDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	infowindow();
	glFlush();
}

/*
* initMenu creates all of the menus and is called for both the info window and the editor window
*/
void initMenu()
{
	int menu_main, submenu_colors, submenu_fonts, submenu_info;

	submenu_colors = glutCreateMenu(menuHandler);
	glutAddMenuEntry("Black", glut_black);
	glutAddMenuEntry("Red", glut_red);
	glutAddMenuEntry("Green", glut_green);
	glutAddMenuEntry("Blue", glut_blue);

	submenu_fonts = glutCreateMenu(menuHandler);
	glutAddMenuEntry("GLUT_BITMAP_8_BY_13", glut_8_BY_13);
	glutAddMenuEntry("GLUT_BITMAP_9_BY_15", glut_9_BY_15);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_10", glut_TIMES_ROMAN_10);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_24", glut_TIMES_ROMAN_24);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_10", glut_HELVETICA_10);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_12", glut_HELVETICA_12);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_18", glut_HELVETICA_18);

	submenu_info = glutCreateMenu(menuHandler);
	glutAddMenuEntry("Show", show_info);
	glutAddMenuEntry("Hide", hide_info);

	menu_main = glutCreateMenu(menuHandler);
	glutAddMenuEntry("Save", save_content);
	glutAddSubMenu("Colors", submenu_colors);
	glutAddSubMenu("Fonts", submenu_fonts);
	glutAddSubMenu("Info", submenu_info);
	glutAddMenuEntry("EXIT", exit_program);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*
* menuHandler handles all of the menu options and their respective functions
*/
void menuHandler(int val)
{
	switch (val)
	{
	case save_content:
		saveContent();
		break;

	case show_info:
		glutSetWindow(infoWindow);
		glutShowWindow();
		glutSetWindow(editorWindow);
		break;

	case hide_info:
		glutSetWindow(infoWindow);
		glutHideWindow();
		glutSetWindow(editorWindow);
		break;

	case glut_black:
		textColor[0] = 0.0;
		textColor[1] = 0.0;
		textColor[2] = 0.0;
		break;

	case glut_red:
		textColor[0] = 1.0;
		textColor[1] = 0.0;
		textColor[2] = 0.0;
		break;

	case glut_green:
		textColor[0] = 0.0;
		textColor[1] = 1.0;
		textColor[2] = 0.0;
		break;

	case glut_blue:
		textColor[0] = 0.0;
		textColor[1] = 0.0;
		textColor[2] = 1.0;
		break;

	case glut_8_BY_13:
		currentFont = GLUT_BITMAP_8_BY_13;
		break;

	case glut_9_BY_15:
		currentFont = GLUT_BITMAP_9_BY_15;
		break;

	case glut_TIMES_ROMAN_10:
		currentFont = GLUT_BITMAP_TIMES_ROMAN_10;
		break;

	case glut_TIMES_ROMAN_24:
		currentFont = GLUT_BITMAP_TIMES_ROMAN_24;
		break;

	case glut_HELVETICA_10:
		currentFont = GLUT_BITMAP_HELVETICA_10;
		break;
	case glut_HELVETICA_12:
		currentFont = GLUT_BITMAP_HELVETICA_12;
		break;

	case glut_HELVETICA_18:
		currentFont = GLUT_BITMAP_HELVETICA_18;
		break;

	case exit_program:
		exit(0);
	}

	editorDisplayCallback();
}

/*
* mouseCallback sets the starting raster position if the user has not typed yet
*/
void mouseCallback(int buttonName, int state, int x, int y)
{
	if (!hasTyped) setStartPos(y);
	//std::cout << "Click at x, y: " << x << ", " << y << std::endl;
}

/*
* keyboardCallback sends all of the keys pressed to the global char vector
*/
void keyboardCallback(unsigned char key, int x, int y)
{
	if (!hasTyped) hasTyped = true;

	if (key == 8 && charList.size() > 0)
	{
		charList.pop_back();
		fontPerChar.pop_back();
	}
	else
	{
		charList.push_back(key);
		fontPerChar.push_back(currentFont);
		//std::cout << "Added a character " << key << " with font #" << currentFont << std::endl;
	}

	editorDisplayCallback();
}

/*
* setStartPos sets the raster starting position whenever the user clicks before typing
*/
void setStartPos(int y)
{
	rasterStartX = -270;
	rasterStartY = findLine(298 - y);
	int start = (y / 20) + 1;
	startLine = start;
	//std::cout << startLine;
}

/*
* saveContent saves all of the content of the global char array to a file
*
* File:
*	open in truncate mode (erases everything in this file if it already exists)
*	named typed.txt
*	directory is C:\Temp\
*/
void saveContent()
{
	std::fstream outFile("C:\\Temp\\typed.txt", std::ios::out | std::ios::trunc);
	for (auto character : charList)
	{
		outFile << character;
	}
	outFile.close();
}

/*
* drawText renders the text from a global unsigned char vector given the current font and color
*/
void drawText()
{
	glColor3f(textColor[0], textColor[1], textColor[2]);
	glRasterPos2i(rasterStartX, rasterStartY);
	int charCountThisLine = 0;
	int charTotalCount = 0;
	int newLineCount = startLine;
	for (auto character : charList)
	{
		int* rasterPos = new int[2];
		glGetIntegerv(GL_CURRENT_RASTER_POSITION, rasterPos);
		if (charCountThisLine >= 125 || *rasterPos > glutGet(GLUT_WINDOW_WIDTH) - 30 || character == 13)
		{
			//go to next line
			charCountThisLine = 0;
			startLine++;
			glRasterPos2i(-270, findLine(300 - (20 * startLine)));
		}
		glutBitmapCharacter(fontPerChar[charTotalCount], character);
		charCountThisLine++;
		charTotalCount++;
	}
	glFlush();
	startLine = newLineCount;
}

/*
*  drawLines draws 30 lines for the editor window to make it look like paper
*/
void drawLines()
{
	//horizontal lines
	glColor3f(0, 0, 0);
	for (int i = -15; i < 15; i++)
	{
		glBegin(GL_POINTS);
		for (int j = -300; j <= 300; j++)
			glVertex2i(j, (i * 20) - 2);
		glEnd();
	}

	//right vertical line
	glColor3f(1, .22, .27);
	glBegin(GL_POINTS);
	for (int i = -300; i < 300; i++)
		glVertex2i(280, i);
	glEnd();

	//left vertical line
	glColor3f(0, .15, .9);
	glBegin(GL_POINTS);
	for (int i = -300; i < 300; i++)
		glVertex2i(-280, i);
	glEnd();

}


/*
* findLine takes in a y coordinate where the origin is in the center of the screen
*	and returns the raster pos of where that line should be in that same coord system
*
* Params:
*	int numToRound		the y coordinate where the origin is in the center (-300 < y > 300)
*
* Return:
*	int					a good pixel position where the raster position y should be
*
*/
int findLine(int numToRound)
{
	if (numToRound > 270)
		return 282;

	int multiple = 10;

	int remainder = numToRound % multiple;
	if (remainder == 0)
		return numToRound;

	if (numToRound % 20 == 0)
		return numToRound + 12;

	return (numToRound - remainder);
}