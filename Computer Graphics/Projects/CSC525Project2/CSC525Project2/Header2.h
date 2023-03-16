#pragma once
#ifndef GLCHAR_H
#define GLCHAR_H

#include "Header1.h"

static const int rowHeight = 18;	// Rows will be 18 world units, leaving 45 units worth of buffer
static int curRow = 0;

// There are 30 rows with 2 parameters each: Y-Position and an array of characters
// Each character inside of the character array will have 5 parameters, R, G, B, Font, and char
static int xRowPosition = 285;

static int typingPositionX = 285;
static int typingPositionY = 268;

static void* selected_font = GLUT_BITMAP_8_BY_13;
static float selected_text_color[3] = { 0,0,0 };

// Font 0 will be GLUT_BITMAP_TIMES_ROMAN_10, font 1 will be GLUT_BITMAP_HELVETICA_10,
// and font 2 will be GLUT_BITMAP_8_BY_13

class glChar {
private:
	char character;
	int red, green, blue;
	void* font;

public:
	void setValues(const char curChar, float curRed, float curGreen, float curBlue, void* curFont);
	void display();
	char getChar();
};


#endif
