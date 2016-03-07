/*
 * font.cpp
 *
 *  Created on: 07-Sep-2013
 *      Author: vignan_pc
 */


#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
void drawBitmapText(char *string,float x,float y,float z)
{
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

