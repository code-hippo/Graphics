/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Color" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "glm.h"
#include "read.h"
#include "trans.h"

using namespace std;

UVN* _read;
GLMmodel* _object;
int i=0;
int i1=0;

void clean() {
	delete _read;
}
//Called when a key is pressed

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

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHT0);glEnable(GL_LIGHT1);glEnable(GL_LIGHT2);glEnable(GL_LIGHT3);glEnable(GL_LIGHT4);glEnable(GL_LIGHT5);glEnable(GL_LIGHT6);glEnable(GL_LIGHT7);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );//Enable color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Change the background to sky blue
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)w / (double)h, 1.0, 200.0);

}

void handleResize2(int w, int h) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
//		for(int i=0;i<3;i++){
//		cout<<eye1[i]<<"pw"<<endl;}
		}

float _angle = 30.0f;
float _cameraAngle = 0.0f;
//Draws the 3D scene
// Somewhere in the initialization part of your program�
//glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); // Create light components

GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

// Assign created components to
//GL_LIGHT0 glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
//glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
//glLightfv(GL_LIGHT0, GL_POSITION, position);
float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

void drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(30*sin(angle),10,-30+30*cos(angle),0,0,-30,0,2,0);
	glScalef(1,1,1);
	glTranslatef(0,0,-30);
	glEnable(GL_LIGHT0);
	glTranslatef(0,0,0);

	glPushMatrix();
	//Draws the 3D scene
	// Somewhere in the initialization part of your program�



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


	//		_read->fileread1();
	vector1 eye= p_wcs_f_vcs(_read,_read->Eye);
  //			glTranslatef(eye[0],eye[1],eye[2]);
  //			if(i1==0){
  //compute_unit_VCS(_read);i1++;}
  //			eye= p_wcs_f_vcs(_read,_read->Eye);
  //			glTranslatef(eye[0],eye[1],eye[1]);

	glPushMatrix();
		glColor3f(0,0.0,0.0);
		glTranslatef(eye[0],eye[1],eye[2]);
		glutSolidCube(.5);
	glPopMatrix();
	//							glPushMatrix();
	//													glColor3f(0,0.0,0.0);
	//														glTranslatef(ey1[0],ey1[1],ey1[2]);
	//														glutSolidCube(.5);
	//														glPopMatrix();
	vector1 wlbn,wlbf;
	vector1 wltn,wltf;
	vector1 wrbn,wrbf;
	vector1 wrtn,wrtf;
	if(i1==0){
		wlbn=p_wcs_f_vcs(_read,_read->wlb);
		wltn=p_wcs_f_vcs(_read,_read->wlt);
		wrbn=p_wcs_f_vcs(_read,_read->wrb);
		wrtn=p_wcs_f_vcs(_read,_read->wrt);

		wlbf=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(_read->far)/(_read->near),eye);
		wltf=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(_read->far)/(_read->near),eye);
		wrbf=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(_read->far)/(_read->near),eye);
		wrtf=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(_read->far)/(_read->near),eye);

		glPushMatrix();
			glTranslatef(5,6,3);
			glScalef(.1,.1,.1);
			glBegin(GL_LINES);
			glmDraw(_object,GLM_COLOR);
			glEnd();
		glPopMatrix();
	}
	else if(i1==1){
		wlbn=p_wcs_f_vcs(_read,_read->wlb);
		wltn=p_wcs_f_vcs(_read,_read->wlt);
		wrbn=p_wcs_f_vcs(_read,_read->wrb);
		wrtn=p_wcs_f_vcs(_read,_read->wrt);

		wlbf=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(10)/(_read->near),eye);
		wltf=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(10)/(_read->near),eye);
		wrbf=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(10)/(_read->near),eye);
		wrtf=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(10)/(_read->near),eye);

		wlbn=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(10)/(_read->far),eye);
		wltn=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(10)/(_read->far),eye);
		wrbn=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(10)/(_read->far),eye);
		wrtn=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(10)/(_read->far),eye);
		glPushMatrix();
			glTranslatef(eye[0],eye[1],eye[2]);
			glScalef((10.0)/_read->far,(10.0)/_read->far,(10.0)/_read->far);
			glTranslatef(-eye[0],-eye[1],-eye[2]);
			glTranslatef(5,6,3);
			glScalef(.1,.1,.1);
			glBegin(GL_LINES);
			glmDraw(_object,GLM_COLOR);
			glEnd();
		glPopMatrix();
	}
	else if(i1==2){
		wlbn=p_wcs_f_vcs(_read,_read->wlb);
		wltn=p_wcs_f_vcs(_read,_read->wlt);
		wrbn=p_wcs_f_vcs(_read,_read->wrb);
		wrtn=p_wcs_f_vcs(_read,_read->wrt);

		wlbf=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(10)/(_read->near),eye);
		wltf=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(10)/(_read->near),eye);
		wrbf=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(10)/(_read->near),eye);
		wrtf=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(10)/(_read->near),eye);

		//wlbn=wlbfeye[2];
		wltn=wltf;wltn[2]=9*eye[2];
		wrbn=wrbf;wrbn[2]=9*eye[2];
		wrtn=wrtf;wrtn[2]=9*eye[2];
		//	wlbn=(p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		//	wltn=(p_from_eye(wltn,magnitude(vsub(wltn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		//	wrbn=(p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		//	wrtn=(p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		//	wlbn[2]=eye[2];wltn[2]=eye[2];wrbn[2]=eye[2];wrbn[2]=eye[2];
		glPushMatrix();
			glTranslatef(eye[0],eye[1],eye[2]);
			glScalef((10.0)/_read->far,(10.0)/_read->far,(10.0)/_read->far);
			glTranslatef(-eye[0],-eye[1],-eye[2]);
			glTranslatef(5,6,3);
			glScalef(.1,.1,.1);
			glBegin(GL_LINES);
			glmDraw(_object,GLM_COLOR);
			glEnd();
		glPopMatrix();
	}
	//vector1 vcs_1=compute_unit_VCS(_read);
	//glScalef(10.0/(2*_read->wr),(10.0)/(2*_read->wt),(10.0)/(2*_read->far));
	// cout<<(1.0)/(2*_read->wr)<<" "<<1.0/(2*_read->wt)<<" "<<1.0/(2*_read->far)<<endl;

	//



	glPushMatrix();
		glColor3f(0.0,0.0,0);
		glBegin(GL_LINES);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glEnd();
		glColor3f(0.0,0.0,0);
		glBegin(GL_LINES);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,0);
		glBegin(GL_LINES);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glEnd();
		glColor4f(.2,0.0,0.0,.4);
		glBegin(GL_QUADS);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glEnd();
	glPopMatrix();



	glutSwapBuffers();
}
void drawScene2() {
	vector1 eye1= p_wcs_f_vcs(_read,_read->Eye);
	float angle3=(180.0/3.14)*(2*atan(_read->wt/_read->near));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle3, (double)_read->wl / (double)_read->wb, _read->near, _read->far);
	gluLookAt(5*angle+eye1[0],eye1[1],eye1[2]-30,_read->Ref[0],
		_read->Ref[1],_read->Ref[2]-30,_read->V[0],_read->V[1],_read->V[2]);

	glTranslatef(0,0,-30);
		//glRotatef(+30,1,0,0);
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

	// 			_read->fileread1();
	vector1 eye= p_wcs_f_vcs(_read,_read->Eye);
	//			glTranslatef(eye[0],eye[1],eye[2]);
	//			if(i1==0){
	//      compute_unit_VCS(_read);i1++;}
	//			eye= p_wcs_f_vcs(_read,_read->Eye);
	//			glTranslatef(eye[0],eye[1],eye[1]);
	glPushMatrix();
		glColor3f(0,0.0,0.0);
		glTranslatef(eye[0],eye[1],eye[2]);
		glutSolidCube(.5);
	glPopMatrix();
	//	glPushMatrix();
	//	glColor3f(0,0.0,0.0);
	//	glTranslatef(ey1[0],ey1[1],ey1[2]);
	//	glutSolidCube(.5);
	//	glPopMatrix();
	vector1 wlbn,wlbf;
	vector1 wltn,wltf;
	vector1 wrbn,wrbf;
	vector1 wrtn,wrtf;
	if(i1==0){
		wlbn=p_wcs_f_vcs(_read,_read->wlb);
		wltn=p_wcs_f_vcs(_read,_read->wlt);
		wrbn=p_wcs_f_vcs(_read,_read->wrb);
		wrtn=p_wcs_f_vcs(_read,_read->wrt);

		wlbf=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(_read->far)/(_read->near),eye);
		wltf=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(_read->far)/(_read->near),eye);
		wrbf=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(_read->far)/(_read->near),eye);
		wrtf=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(_read->far)/(_read->near),eye);

		glPushMatrix();
			glTranslatef(5,6,3);
			glScalef(.1,.1,.1);
			glBegin(GL_LINES);
			glmDraw(_object,GLM_COLOR);
			glEnd();
		glPopMatrix();
	}
	else if(i1==1){
		wlbn=p_wcs_f_vcs(_read,_read->wlb);
		wltn=p_wcs_f_vcs(_read,_read->wlt);
		wrbn=p_wcs_f_vcs(_read,_read->wrb);
		wrtn=p_wcs_f_vcs(_read,_read->wrt);

		wlbf=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(10)/(_read->near),eye);
		wltf=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(10)/(_read->near),eye);
		wrbf=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(10)/(_read->near),eye);
		wrtf=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(10)/(_read->near),eye);

		wlbn=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(10)/(_read->far),eye);
		wltn=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(10)/(_read->far),eye);
		wrbn=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(10)/(_read->far),eye);
		wrtn=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(10)/(_read->far),eye);

		glPushMatrix();
			glTranslatef(eye[0],eye[1],eye[2]);
			glScalef((10.0)/_read->far,(10.0)/_read->far,(10.0)/_read->far);
			glTranslatef(-eye[0],-eye[1],-eye[2]);
			glTranslatef(5,6,3);
			glScalef(.1,.1,.1);
			glBegin(GL_LINES);
			glmDraw(_object,GLM_COLOR);
			glEnd();
		glPopMatrix();
	}
	else if(i1==2){
		wlbn=p_wcs_f_vcs(_read,_read->wlb);
		wltn=p_wcs_f_vcs(_read,_read->wlt);
		wrbn=p_wcs_f_vcs(_read,_read->wrb);
		wrtn=p_wcs_f_vcs(_read,_read->wrt);

		wlbf=p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*(10)/(_read->near),eye);
		wltf=p_from_eye(wltn,magnitude(vsub(wltn,eye))*(10)/(_read->near),eye);
		wrbf=p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*(10)/(_read->near),eye);
		wrtf=p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*(10)/(_read->near),eye);

		//wlbn=wlbfeye[2];
		wltn=wltf;wltn[2]=9*eye[2];
		wrbn=wrbf;wrbn[2]=9*eye[2];
		wrtn=wrtf;wrtn[2]=9*eye[2];
		wrtn=wrbf;wrtn[2]=9*eye[2];

		// wlbn=(p_from_eye(wlbn,magnitude(vsub(wlbn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		// wltn=(p_from_eye(wltn,magnitude(vsub(wltn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		// wrbn=(p_from_eye(wrbn,magnitude(vsub(wrbn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		// wrtn=(p_from_eye(wrtn,magnitude(vsub(wrtn,eye))*((10*_read->far)/_read->near)/(_read->far),eye));
		// wlbn[2]=eye[2];wltn[2]=eye[2];wrbn[2]=eye[2];wrbn[2]=eye[2];
		glPushMatrix();
			glTranslatef(eye[0],eye[1],eye[2]);
			glScalef((10.0)/_read->far,(10.0)/_read->far,(10.0)/_read->far);
			glTranslatef(-eye[0],-eye[1],-eye[2]);
			glTranslatef(5,6,3);
			glScalef(.1,.1,.1);
			glBegin(GL_LINES);
			glmDraw(_object,GLM_COLOR);
			glEnd();
		glPopMatrix();
	}
	//vector1 vcs_1=compute_unit_VCS(_read);
	//glScalef(10.0/(2*_read->wr),(10.0)/(2*_read->wt),(10.0)/(2*_read->far));
	// cout<<(1.0)/(2*_read->wr)<<" "<<1.0/(2*_read->wt)<<" "<<1.0/(2*_read->far)<<endl;

	glPushMatrix();
		glColor3f(0.0,0.0,0);
		glBegin(GL_LINES);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glEnd();
		glColor3f(0.0,0.0,0);
		glBegin(GL_LINES);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,0);
		glBegin(GL_LINES);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glEnd();
		glColor4f(.2,0.0,0.0,.4);
		glBegin(GL_QUADS);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(wrbn[0],wrbn[1],wrbn[2]);
		glVertex3f(wrbf[0],wrbf[1],wrbf[2]);
		glVertex3f(wrtf[0],wrtf[1],wrtf[2]);
		glVertex3f(wrtn[0],wrtn[1],wrtn[2]);
		glEnd();
		glBegin(GL_QUADS);
		glVertex3f(wltn[0],wltn[1],wltn[2]);
		glVertex3f(wltf[0],wltf[1],wltf[2]);
		glVertex3f(wlbf[0],wlbf[1],wlbf[2]);
		glVertex3f(wlbn[0],wlbn[1],wlbn[2]);
		glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	keyoperations();
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

GLenum fillMode =GL_SMOOTH;
void filloption(GLint selectedoption){
	switch(selectedoption){
	case 1: fillMode=GL_FLAT; break;  //Flat surface rendering
	case 2: fillMode=GL_SMOOTH;break; //Gouraud rendering
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 600);
	//UVN * read;
	_read =load();
	_read->fileread1();
	//vector1 eye= p_wcs_f_vcs(_read,_read->Eye);
	//
	_object  = glmReadOBJ("Kroserica_simple2.obj");
	//Create the window
	int win1=glutCreateWindow("3D Viewing Pipeline -with Viewing Transformation in the subwindow");

	glutReshapeFunc(handleResize);
	glutDisplayFunc(drawScene);
	glutCreateMenu(filloption);
	glutAddMenuEntry("runbun",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardFunc(keypressed);
	glutKeyboardUpFunc(keyup);
	//	glutCreateWindow("Color - videotutorialsrock.com");
	//glutCreateSubWindow(win1, 600, 400,300, 200);

	initRendering();
	int win2= glutCreateSubWindow(win1, 600, 400,300, 200);

	//read= load();
	//Set handler functions
	//		glutInitWindowSize(400, 300);
	//		glutCreateWindow("Color - videotutorialsrock.com");
	//		initRendering();
	glutReshapeFunc(handleResize2);
	glutDisplayFunc(drawScene2);
	glutKeyboardFunc(handleKeypress2);
	glutKeyboardFunc(keypressed);
	glutKeyboardUpFunc(keyup);
	initRendering();

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}
