
#include<stdlib.h>
#include<GL/glut.h>
#include "Header1.h"
#include "Header2.h"


// To allow file reading
#include <fstream>
using std::ifstream;

// To exit if the file doesn't exist
#include <cstdlib>

int mainWindow;		// id for the main window
int infoWindow;		// id for the help window
int editorWindow;	// id for the editor subwindow
int menuWindow;		// id for menu subwindow

bool hasTyped = false;

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
	exit_program,
	show_info,
	hide_info
};

void textMenu();
void menu_handler(int); // Menu handling function declaration
void saveContent();



void textMenu() {

	glClearColor(.5, .5, .5, 0);			// specify a background clor: blueish-green
	gluOrtho2D(-400, 400, -19, 0);  // specify a viewing area

	int menu_main, submenu_colors, submenu_fonts, submenu_info;

	submenu_colors = glutCreateMenu(menu_handler);
	glutAddMenuEntry("Black", glut_black);
	glutAddMenuEntry("Red", glut_red);
	glutAddMenuEntry("Green", glut_green);
	glutAddMenuEntry("Blue", glut_blue);

	submenu_fonts = glutCreateMenu(menu_handler);
	glutAddMenuEntry("GLUT_BITMAP_8_BY_13", glut_8_BY_13);
	glutAddMenuEntry("GLUT_BITMAP_9_BY_15", glut_9_BY_15);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_10", glut_TIMES_ROMAN_10);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_24", glut_TIMES_ROMAN_24);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_10", glut_HELVETICA_10);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_12", glut_HELVETICA_12);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_18", glut_HELVETICA_18);

	submenu_info = glutCreateMenu(menu_handler);
	glutAddMenuEntry("Show", show_info);
	glutAddMenuEntry("Hide", hide_info);

	menu_main = glutCreateMenu(menu_handler);
	glutAddMenuEntry("Save", save_content);
	glutAddSubMenu("Colors", submenu_colors);
	glutAddSubMenu("Fonts", submenu_fonts);
	glutAddSubMenu("Info", submenu_info);
	glutAddMenuEntry("EXIT", exit_program);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_LEFT_BUTTON);

}

// Menu handling function definition
void menu_handler(int item)
{
	switch (item)
	{

	case save_content:
		saveContent();
		break;

	case show_info:
		glutSetWindow(infoWindow);
		glutShowWindow();
		glutSetWindow(mainWindow);
		break;

	case hide_info:
		glutSetWindow(infoWindow);
		glutHideWindow();
		glutSetWindow(mainWindow);
		break;

	case glut_black:
		selected_text_color[0] = 0.0;
		selected_text_color[1] = 0.0;
		selected_text_color[2] = 0.0;
		break;

	case glut_red:
		selected_text_color[0] = 1.0;
		selected_text_color[1] = 0.0;
		selected_text_color[2] = 0.0;
		break;

	case glut_green:
		selected_text_color[0] = 0.0;
		selected_text_color[1] = 1.0;
		selected_text_color[2] = 0.0;
		break;

	case glut_blue:
		selected_text_color[0] = 0.0;
		selected_text_color[1] = 0.0;
		selected_text_color[2] = 1.0;
		break;

	case glut_8_BY_13:
		selected_font = GLUT_BITMAP_8_BY_13;
		break;

	case glut_9_BY_15:
		selected_font = GLUT_BITMAP_9_BY_15;
		break;

	case glut_TIMES_ROMAN_10:
		selected_font = GLUT_BITMAP_TIMES_ROMAN_10;
		break;

	case glut_TIMES_ROMAN_24:
		selected_font = GLUT_BITMAP_TIMES_ROMAN_24;
		break;

	case glut_HELVETICA_10:
		selected_font = GLUT_BITMAP_HELVETICA_10;
		break;
	case glut_HELVETICA_12:
		selected_font = GLUT_BITMAP_HELVETICA_12;
		break;

	case glut_HELVETICA_18:
	{
		selected_font = GLUT_BITMAP_HELVETICA_18;
	}
	break;

	
	default:
	{
		selected_font = GLUT_BITMAP_8_BY_13;
	}
	break;
	}

	glutPostRedisplay();
	return;
}

std::vector<glChar> text;

void letterInput(unsigned char key, int xMouse, int yMouse) {
	switch (key)
	{
	case 8:
		if (text.size() > 0) {
			text.pop_back();
			glutPostRedisplay();
		}
		break;
	case 13:
		glChar enter;
		enter.setValues('\n', selected_text_color[0], selected_text_color[1], selected_text_color[2], selected_font);
		text.push_back(enter);
		break;
	default:
		glChar tmp;
		tmp.setValues(key, selected_text_color[0], selected_text_color[1], selected_text_color[2], selected_font);
		text.push_back(tmp);
		break;
	}
	hasTyped = true;
	glutPostRedisplay();
}

void mouseInput(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !hasTyped) {

		int yWorld = y / 1.28 - 300;
		for (int i = 1; i <= 30; i++) {
			if (typingPositionY - i * rowHeight >= yWorld)
			{
				curRow = 30 - i;
			}
		}
		glutPostRedisplay();

	}
	else {
	}
}

void drawEditor() {
	glutSetWindow(editorWindow);	// Sets window to editor

	int drawLinePosition = 250; //accounting for menu at top and 25 unit buffer

	glPointSize(1);

	for (int i = 0; i < 30; i++)
	{
		glBegin(GL_LINES);
		glColor3f(.9, .9, .9);
		glVertex2i(-xRowPosition, drawLinePosition);
		glVertex2i(xRowPosition, drawLinePosition);
		glEnd();
		drawLinePosition -= rowHeight;
	}

	glRasterPos2i(typingPositionX, typingPositionY - curRow * rowHeight + 3);

	// Iterates over text vector and displays all current text
	for (auto i : text) {
		i.display();
	}
	if (hasTyped) {
		GLfloat pos[4];
		glGetFloatv(GL_CURRENT_RASTER_POSITION, pos);
		float xPosition = pos[0] / 1.28 - 300;
		float yPosition = pos[1] / 1.28 - 300;

		glBegin(GL_LINE_STRIP);
		glColor3f(selected_text_color[0], selected_text_color[1], selected_text_color[2]);
		glVertex2i(xPosition + 5, yPosition);
		glVertex2i(xPosition + 10, yPosition);
		glVertex2i(xPosition + 10, yPosition + 10);
		glVertex2i(xPosition + 5, yPosition + 10);
		glVertex2i(xPosition + 5, yPosition);
		glEnd();
	}
	else
	{
		glBegin(GL_LINE_STRIP);
		glColor3f(selected_text_color[0], selected_text_color[1], selected_text_color[2]);
		glVertex2i(-typingPositionX, typingPositionY - curRow * rowHeight - 15);
		glVertex2i(-typingPositionX + 5, typingPositionY - curRow * rowHeight - 15);
		glVertex2i(-typingPositionX + 5, typingPositionY - curRow * rowHeight - 5);
		glVertex2i(-typingPositionX, typingPositionY - curRow * rowHeight - 5);
		glVertex2i(-typingPositionX, typingPositionY - curRow * rowHeight - 15);
		glEnd();
	}
}

void drawText(int win, float x, float y, float r, float g, float b, std::string text) {
	glutSetWindow(win);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(x, y);
	void* font = GLUT_BITMAP_8_BY_13;
	for (string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

void drawMenu() {
	drawText(menuWindow, -10, 5, 1.0, 1.0, 1.0, "Menu");
}

void drawInfo() {
	drawText(infoWindow, -190, 260, 1.0, 0.0, 0.0, "This text editor allows you to type text on ");
	drawText(infoWindow, -190, 240, 1.0, 0.0, 0.0, "any line. The text editor also allows you to ");
	drawText(infoWindow, -190, 220, 1.0, 0.0, 0.0, "change color and font for any text typed ");
	drawText(infoWindow, -190, 200, 1.0, 0.0, 0.0, "after selecting the new font/color.");

	drawText(infoWindow, -190, 160, 1.0, 0.0, 0.0, "Instructions for changing font/color:");
	drawText(infoWindow, -190, 140, 1.0, 0.0, 0.0, "1. Click the grey menu bar at the top of the");
	drawText(infoWindow, -190, 120, 1.0, 0.0, 0.0, "   editor window.");
	drawText(infoWindow, -190, 100, 1.0, 0.0, 0.0, "2. Select an option.");
}

void mainInit() {
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-300, 300, -300, 300);  // specify a viewing area

}

void editorInit() {
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-300, 300, -300, 275);  // specify a viewing area
	glutSetCursor(GLUT_CURSOR_TEXT);
	glutMouseFunc(mouseInput);
	glutKeyboardFunc(letterInput);
}

void menuInit() {
	glClearColor(.75, .75, .75, 0);			// specify a background
	gluOrtho2D(-10, 300, -10, 19);  // specify a viewing area

	textMenu();
}

void infoInit() {
	glClearColor(.40, .40, .40, 0);			// specify a background
	gluOrtho2D(-200, 200, -300, 300);  // specify a viewing area
}


void saveContent() {
	//FIXME
	cout << "Saving content..." << endl;

	// Removes any previous version of typed.txt
	remove("C:\\TEMP\\typed.txt");

	ofstream ResultFile("C:\\TEMP\\typed.txt");

	for (auto i : text) {
		ResultFile << i.getChar();
	}

}

//***********************************************************************************
void myDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawMenu();
	drawEditor();
	drawInfo();

	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(384, 576);							// specify a window size
	glutInitWindowPosition(50, 50);							// specify a window position
	infoWindow = glutCreateWindow("Info/Help");
	infoInit();
	glutDisplayFunc(myDisplayCallback);

	glutInitWindowSize(768, 768);							// specify a window size
	glutInitWindowPosition(500, 50);							// specify a window position
	mainWindow = glutCreateWindow("Simple Text Editor");	// create a titled window
	mainInit();									// setting up
	glutDisplayFunc(myDisplayCallback);		// register a callback

	menuWindow = glutCreateSubWindow(mainWindow, 0, 0, 768, 32);
	menuInit();
	glutDisplayFunc(myDisplayCallback);


	// Initialize editor window last so that user can begin typing
	editorWindow = glutCreateSubWindow(mainWindow, 0, 32, 768, 736);
	editorInit();
	glutDisplayFunc(myDisplayCallback);


	glutMainLoop();							// get into an infinite loop
	return 1;
}