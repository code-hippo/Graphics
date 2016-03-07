//============================================================================
// Name        : pixar.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * main.cpp
 *
 *  Created on: 18-Aug-2013
 *      Author: vignan_pc
 */

#include "pixar.h"
#include <GL/glut.h>

uni* uni1;
//#define KEY_ESCAPE 27

void clean() {
	//delete _Object;
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}
void handleKeypress2(unsigned char key, int x, int y) {
	switch (key) {
		case 'q': //Escape key
			exit(0);
	}
}

float angle =0;
float angle2 =0;
int i=0;
int i1=0;
bool* Keystates = new bool[ 256];

void keyoperations()
{
if(Keystates['a']){
	angle-=.02;
}
if(Keystates['d']){
	angle +=.02;
}
if(Keystates['w']){
	angle2+=.02;
}
if(Keystates['s']){
	angle2 -=.02;
}
if(Keystates['v']){
	i1=0;
}
if(Keystates['n']){
	i1=1;
}
if(Keystates['p']){
	i1=2;
}
}

void keypressed(unsigned char a,int x, int y)
{
	Keystates[ a ] =true;
}

void keyup(unsigned char a,int x,int y)
{
    Keystates[ a] =false;
}
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	//
	glEnable(GL_NORMALIZE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

	//t3dInit();
}

void drawScene() {
	cons(uni1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(90.0, (double)1000 / (double)1000,1.0, 200.0);
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	gluLookAt(30*sin(angle)*cos(angle2),10-20*sin(angle2),30*cos(angle)*cos(angle2),0,0,0,0,2,0);
	glScalef(1,1,1);
	GLfloat ambientColor[] = {0.6f, 0.6f, 0.6f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	glPushMatrix();
	ball(uni1->ball);

	glPopMatrix();
	glPushMatrix();

	for(int i=-45;i<45;i++){
		for(int j=-45;j<45;j++){
	glBegin(GL_QUADS);
	if((i+j)%2){
		glColor3f(1,1,1);
	}
	else{
		glColor3f(0,0,0);
	}
	glVertex3f(i,0,j);
	glVertex3f(i,0,j+1);
	glVertex3f(i+1,0,j+1);
	glVertex3f(i+1,0,j);
	glEnd();
		}
	}
	glPopMatrix();

	//lamp hierarchy
	glPushMatrix();

	glColor3f(3,0,0);
	//cylinder
  glPushMatrix();
  cylinder(uni1,1,1);
	//Sphere
  glPushMatrix();
  sphere(uni1,1,1);
	//Cylinder
  glPushMatrix();
  cylinder(uni1,1,2);
	//sphere
  glPushMatrix();
  sphere(uni1,1,2);
	// glEnable(GL_LIGHT0);
  //cylinder
	glPushMatrix();
	cylinder(uni1,1,3);
  //bulb
	glPushMatrix();
	sphere(uni1,1,3);
	glTranslatef(3,3,0);
	glPopMatrix();		glPopMatrix();
	glPopMatrix();	    glPopMatrix();
	glPopMatrix();	    glPopMatrix();
	glPopMatrix();
	//glEnd();

	//lamp hierarchy
	glPushMatrix();
	glColor3f(3,0,0);
	//cylinder
	glPushMatrix();
	cylinder(uni1,0,1);
	//Sphere
	glPushMatrix();
	sphere(uni1,0,1);
	//Cylinder
	glPushMatrix();
	cylinder(uni1,0,2);
	//sphere
	glPushMatrix();
	sphere(uni1,0,2);
	// glEnable(GL_LIGHT0);
	//cylinder
	glPushMatrix();
	cylinder(uni1,0,3);
	//bulb
	glPushMatrix();
	sphere(uni1,0,3);
	glTranslatef(3,3,0);
	glPopMatrix();		glPopMatrix();
	glPopMatrix();	    glPopMatrix();
	glPopMatrix();	    glPopMatrix();
	glPopMatrix();
	//glEnd();
//end

	glTranslatef(0,0,0);

	glPushMatrix();
	glTranslatef(0,0,0);
	glColor3f(0.0,0,0);
	glutSolidCube(.2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,+10);
	glColor3f(0,0.0,1.0);
	glutSolidCube(.2);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(10,0,0);
	glutSolidCube(.2);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0,1.0,0.0);
	glTranslatef(0,10,0);
	glutSolidCube(.2);
	glPopMatrix();

  // glTranslatef(0,0,-5);
	glPushMatrix();
	glColor3f(0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,0,10);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(10,0,0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0,1.0,.0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,10,0);
	glEnd();
	glPopMatrix();



	//GLfloat x=-25;
	for(int x=-45;x<46;x++)
	{
		glPushMatrix();
		glColor3f(0.5,0.4,.3);
		glBegin(GL_LINES);
		glVertex3f(x,0,-45);
		glVertex3f(x,0,45);
		glEnd();
		glPopMatrix();
		x=x+4;
	}
	for(int z=-45;z<46;z++)
	{
		glPushMatrix();
	  glColor3f(0.5,0.4,0.3);
		glBegin(GL_LINES);
		glVertex3f(45,0,z);
		glVertex3f(-45,0,z);
		glEnd();
		glPopMatrix();
		z=z+4;
	}

	glutSwapBuffers();
}


void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void update(int value) {
	keyoperations();
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv)
{
	printf ("dvasd");
	uni1=memory();
	//uni1->ball->vel[0]=2;
  uni1->ball->rad=2;
	glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Pixar");
	initRendering();

	glutReshapeFunc(handleResize);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
  glutKeyboardFunc( keypressed );
  glutKeyboardUpFunc( keyup);                                   // register Keyboard Handler
  glutTimerFunc(25,update,0);

	glutMainLoop();

	return 0;
}
//glTranslatef( 5.886971, -17.172176, -29.579876)
//glTranslatef(5.890946, -17.203533, 21.340796)
