/**
 * @file
 *@author VIGNAN,BHARGAV,AVINASH
 *@version 1.0
 *@note The readdata.cpp,Writing text are taken And edited to our convienence from videotutorialsrock.com
 */

#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "math.h"
#include <iostream>
#include "readData.h"
#include "vector3f.h"
#include"terrain.h"
#include "texture.h"
#include "glm.h"
#include "physics.h"
#include "font1.h"
#include "screenscore.h"
#include "highscores.h"
#include "Obst.h"

using namespace std;

const float TERRAIN_WIDTH = 50.0f;
const float obstsize=10;
const float PI = 3.1415926535f;

Object* _Object;
terrain* _terrain;
GLuint _textureId;
GLuint _textureId1;
GLMmodel* _object;


float time1=0;
float _angle=45.0;
#define KEY_ESCAPE 27

void clean() {
	delete _terrain;
	delete _object;
	delete _Object;
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	t3dInit();
}

void handleKeypress(unsigned char key, int x, int y) {
	if (key==27) {
		clean();
		exit(1);
	}
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawTime(300-time1);


	drawscore(_Object->score);
	if(10-time1<0){
		drawover();
	}
	drawVelocity(magnitude(setvalues(_Object->velocity.x,0,_Object->velocity.z)));
	drawDist(_Object->distance);
	if(_Object->l/2==0)
	{
		gluLookAt(_Object->posonterrain().x-_Object->glulookat().x,_Object->posonterrain().y+_Object->glulookat().y,_Object->posonterrain().z-10-_Object->glulookat().z,
          _Object->posonterrain().x,_Object->posonterrain().y,_Object->posonterrain().z-10,0,2,0);
	}
	else
	{
		gluLookAt(_Object->posonterrain().x-(_Object->glulookat().x)/1.6,_Object->posonterrain().y+(_Object->glulookat().y)/1.6,_Object->posonterrain().z-10-(_Object->glulookat().z)/1.6,
	          _Object->posonterrain().x,_Object->posonterrain().y,_Object->posonterrain().z-10,0,2,0);
	}
	glTranslatef(0.0f, 0.0f, -10.0f);
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-1.0f, -1.0f, -1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	float scale = 50.0f / max(_terrain->width() - 1, _terrain->length() - 1);
	glScalef(scale, scale, scale);
	glTranslatef(-(float)(_terrain->width() - 1) / 2,0.0f, -(float)(_terrain->length() - 1) / 2);
	glPushMatrix();

	for (int i=0;i<10;i++){
    glPushMatrix();
		glTranslatef(_Object->p[2*i],heightAt(_terrain,_Object->p[2*i],_Object->p[2*i+1])+18*_Object->size0+.8,_Object->p[2*i+1]);
		glutSolidCube(2.2);
	  glPopMatrix();
	}
	glPopMatrix();
	for (int i=0;i<10;i++){
		glPushMatrix();
		glTranslatef(_Object->gp[2*i],heightAt(_terrain,_Object->gp[2*i],_Object->gp[2*i+1])+18*_Object->size0+.8,_Object->gp[2*i+1]);
                  glColor3f(0.0,1.0,0.0);
		glutSolidCube(2.2);
		glPopMatrix();
	}
	glPopMatrix();
	for (int i=0;i<10;i++){
	  glPushMatrix();
		glTranslatef(_Object->rp[2*i],heightAt(_terrain,_Object->rp[2*i],_Object->rp[2*i+1])+18*_Object->size0+.8,_Object->rp[2*i+1]);
		glutSolidCube(2.2);
		glColor3f(1,0,0);

	  glPopMatrix();
	}
	glPopMatrix();

	for(int z = 0; z < _terrain->length() -1; z++) {
		glBegin(GL_TRIANGLE_STRIP);

		for(int x = 0; x < _terrain->width()-1; x++) {
			vector3f normal = _terrain->getNormal(x, z);
			glColor3f( 1.0f, 1.0f, 1.0f);
			glNormal3f(normal.x, normal.y, normal.z);
			glTexCoord2f(x/(256.0),z/(256.0));
			glVertex3f(x, _terrain->getHeight(x, z), z);

			normal = _terrain->getNormal(x, z + 1);

			glNormal3f(normal.x, normal.y, normal.z);
			glTexCoord2f(x/256.0,(z+1)/256.0);
			glVertex3f(x, _terrain->getHeight(x, z + 1), z + 1);
		}
		glEnd();
  }

	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	_Object->draw();
	glPopMatrix();

	glutSwapBuffers();
}

int winwidth = 1000;
int winheight = 1000;
string wintitle = "OpenGL/GLUT Window.";
float viewangle_field = 90;
float near_z = .04f;
float far_z = 500.0f;

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect = (GLfloat) winwidth / winheight;
	gluPerspective(viewangle_field, aspect, near_z, far_z);		// set up a perspective projection matrix

}

bool* Keystates = new bool[ 256];

void keyoperations()
{
  if(time1>300){
  	exit(1);
  }
	if(_Object->pos.y<heightAt(_terrain,_Object->pos.x,_Object->pos.z)+18*_Object->size0+6){
		float t=magnitude(_Object->velocity);

		if(Keystates['w'])
		{
			_Object->w=1;
		}
		else _Object->w=0;
		if(Keystates['l'])
		{
			if(_Object->l==1){
				_Object->l=0;
			}
			else _Object->l=1;
		}
		if(Keystates['p'])
		{
			if(_Object->pause==1){
				_Object->pause=0;
			}
			else _Object->pause=1;
		}

		if(Keystates['n'])
		{
			_Object->n=1;
		}
		else _Object->n=0;

		if(Keystates[27]){
			exit(1);
		}

		if(Keystates['a'])
		{
		 	_Object->a=1;
	  }
	  else{
			_Object->a=0;
		}

		if(Keystates['d'])
		{
	    _Object->d=1;
		}
		else _Object->d=0;

		if(Keystates['s'])
		{
			_Object->s=1;
		}
		else _Object->s=0;

		if (Keystates[' '])
		{
	    _Object->sp=1;
		}
		else _Object->sp=0;

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

void update(int value) {
	if(10-time1==0){
		_Object->velocity.x=0;_Object->velocity.y=0;_Object->velocity.z=0;
	}
	if(_Object->pause==1)
	{
		keyoperations();
		glutPostRedisplay();
		glutTimerFunc(25, update, 0);
	}

	else{
	 	keyoperations();
	 	_angle+=0.3f;
	 	time1=time1+0.025;
		if (_angle > 360)
		{
			_angle -= 360;
		}
		_Object->framestime(25);

		glutPostRedisplay();
		glutTimerFunc(25, update, 0);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	char* name;
	name=new char[20];
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winwidth, winheight);
	cout<<"Enter Player's Name:"<<endl;
	cin>>name;
	glutCreateWindow("RaceGame");
	initRendering();
	Image* image1 = loadImage("2texture.bmp");
	_textureId = readTexture(image1);

	delete image1;
	Image* image2 = loadImage("Grass.bmp");
	_textureId1 = readTexture(image2);
	delete image2;
	_terrain = createTerrain("123.bmp", 50.0);
	_object  = glmReadOBJ("Kroserica_simple2.obj");
	_Object  = load(_terrain,_object);

	glutReshapeFunc(handleResize);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
  glutKeyboardFunc( keypressed );
  glutKeyboardUpFunc( keyup);                                   // register Keyboard Handler
  glutTimerFunc(25,update,0);

  scoreupdate(name,_Object->score);

	glutMainLoop();
	return 0;
}
//glTranslatef( 5.886971, -17.172176, -29.579876)
//glTranslatef(5.890946, -17.203533, 21.340796)
