


#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Def.h"
#include "Vector3f.h"
#include "RayTracer.h"
#include "RenderTarget.h"
#include "Scene.h"
//#include "glm.h"

using namespace std;

#define w 960
#define h 600

RenderTarget *	renderTarget = new RenderTarget(w, h);
RayTracer *		rayTracer = new RayTracer(renderTarget);




void clean() {
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

bool* Keystates = new bool[ 256];
GLfloat angle,angle2,_angle =0.0;
int i1=0;
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
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHT0);glEnable(GL_LIGHT1);glEnable(GL_LIGHT2);glEnable(GL_LIGHT3);glEnable(GL_LIGHT4);glEnable(GL_LIGHT5);glEnable(GL_LIGHT6);glEnable(GL_LIGHT7);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );//Enable color
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Change the background to sky blue
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void handleResize(int w1, int h1) {
	glViewport(0, 0, w1, h1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90.0, (double)w / (double)h, 1.0, 200.0);

}
//void Draw()
//{
//	if (renderTarget->GetBuffer())
//	{
//		StretchDIBits(hdc, 0, 0, w, h, 0, 0, w, h, renderTarget->GetBuffer(), renderTarget->GetBitmapInfo(), DIB_RGB_COLORS, SRCCOPY);
//		ValidateRect(hWnd, NULL);
//	}
//}

void drawScene() {



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Pixel* buffer= renderTarget->GetBuffer();
//		for(int i=0;i<w*h;i++){
//			buffer[i]=256;
//		}
		glScalef(1.0/500,1.0/315,1);

		//while(!rayTracer->Render()){
		for(int i=0;i<h;i++){

			//cout<<"i"<<i<<endl;
				for(int i1=0;i1<w;i1++){

				unsigned int p=buffer[i*w+i1];
				//	cout<<"p"<<p<<" i1"<<i1;
					glPushMatrix();
					//glColor3f(1.0,1.0,0.5);
					glColor3f((p >> 16)/256.0,((p>>8) -((p>> 16)<<8))/256.0,(p-((p>>8)<<8))/256.0);
	//glTranslatef(.3,.3,.3);
					glBegin(GL_QUADS);
	                glVertex2f(480-i1,300-i);
	                glVertex2f(480-i1+1,300-i);
	                glVertex2f(480-i1+1,300-i+1);
	                glVertex2f(480-i1,300-i+1);
	                glEnd();
					glPopMatrix();

				}
		}


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
//float f(Vector3f &vec1){
//		return vec1.x;
//	}
int main(int argc, char** argv) {
	//Initialize GLUT
	Vector3f *a=new Vector3f(2.0,1.0,2.0);
	rayTracer->Initialize();
	renderTarget->Clear(0);
	rayTracer->Render();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);

	int win1=glutCreateWindow("Color");

	glutReshapeFunc(handleResize);
			
	glutDisplayFunc(drawScene);
	glutCreateMenu(filloption);
	glutAddMenuEntry("runbun",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardFunc(keypressed);
	glutKeyboardUpFunc(keyup);


	initRendering();

//	glutTimerFunc(25, update, 0); //Add a timer
	glutMainLoop();
	return 0;
}
//int main (){
//	Vector3f a(1.0,2.0,3.0);
//	Vector3f B(5.0,4.0,4.0);
//	Vector3f b=Vector3f(5.0,4.0,4.0)-a;
//	b.Normalize();
//	return 0;
//}









