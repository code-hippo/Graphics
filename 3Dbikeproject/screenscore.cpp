/*
 * screenscore.cpp
 *
 *  Created on: 08-Sep-2013
 *      Author: vignan_pc
 */


#include <sstream>
#include <string>
#include <stdlib.h>
#include "font1.h"
#include <GL/glut.h>
#include "screenscore.h"
using namespace std;
float decimalval(float num){
	int temp=(int)num;
	float dec=num-temp;
	return dec;
}
void drawTime(float Time) {
	ostringstream oss;

	float _Time;
	if(decimalval(Time)<0.5){
		_Time=(int)Time;
	}
	else if(decimalval(Time)>=0.5){
		_Time=(int)Time+1;
	}
	oss << "Time: " << _Time;
	string str = oss.str();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(4.0f, .7f, -7.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	t3dDraw2D(str, 0, 0);


	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawVelocity(float Time) {
	ostringstream oss;

	float _Time;
	if(decimalval(Time*100000)<0.5){
		_Time=(int)(Time*100000);
	}
	else if(decimalval(Time*100000)>=0.5){
		_Time=(int)(Time*100000)+1;
	}
	oss << "Velocity: " << _Time/100<<"m/s";
	string str = oss.str();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-3.0f, 6.7f, -7.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	t3dDraw2D(str, 0, 0);


	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawDist(float Time) {
	ostringstream oss;

	float _Time;
	if(decimalval(Time*10)<0.5){
		_Time=(int)(Time*10)/9;
	}
	else if(decimalval(Time*10)>=0.5){
		_Time=(int)(Time*10)/9+1;
	}
	oss << "Distance: " << _Time/1000<<"km";
	string str = oss.str();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, +6.7f, -7.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	t3dDraw2D(str, 0, 0);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawscore(int score){
	ostringstream oss;
	float _Time;

	oss << "score:"<< score;
	string str = oss.str();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(2.0f, +6.7f, -7.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	t3dDraw2D(str, 0, 0);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawover() {
	ostringstream oss;
	float _Time;
	oss << "GAMEOVER" ;
	string str = oss.str();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	t3dDraw2D(str, 0, 0);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}
