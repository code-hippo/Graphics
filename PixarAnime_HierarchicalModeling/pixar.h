/*
 * pixar.h
 *
 *  Created on: Nov 3, 2014
 *      Author: bhargavvar
 */

#ifndef PIXAR_H_
#define PIXAR_H_

//void gluCylinder(GLUquadric*  quad,  GLdouble  base,  GLdouble  top,  GLdouble  height,  GLint  slices,  GLint  stacks);
//void glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
//void glutWireCone(GLdouble base, GLdouble height,  GLint slices, GLint stacks);
#include <iostream>
#include "stdio.h"
#include <cstdlib>
#include <stdlib.h>
#include <GL/gl.h>

#include "string.h"
#include <GL/glu.h>
//#include "cmath"
#include "math.h"
#include <vector>
#include <iostream>
#include "texture.h"
#include "readData.h"

using namespace std;

typedef vector< int > vi;
typedef vector< float > vf;
const float PI = 3.1415926535f;

typedef struct balls{
	vf pos;
	vf vel;
	float rad;
}balls;

typedef struct slamp{
	vf posb;
	vf vel;
	vf ang;
	vf angv;
}slamp;

typedef struct uni{
	balls* ball;
	slamp* lamp2;
	slamp* lamp1;
}uni;

void cons(uni * p);
vf mem();

uni* memory();
struct zeromemory_t{};
extern  const zeromemory_t zeromemory;

void* operator new(size_t cbSize, const zeromemory_t&);

void ball(balls* ball);
void cylinder(uni* uni,int a,int r);
void sphere(uni* uni,int a,int r);


#endif /* PIXAR_H_ */
