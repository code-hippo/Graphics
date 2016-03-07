/*
 * vector3f3f3f.cpp
 *
 *  Created on: 12-Aug-2013
 *      Author: vignan_pc
 */

#include "math.h"
#include<iostream>
#include "vector3f.h"


float magnitude(vector3f a){
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

vector3f sum(vector3f a,vector3f b){
	vector3f c;
	c.x=a.x+b.x;
	c.y=a.y+b.y;
	c.z=a.z+b.z;
	return c;
}

vector3f sub(vector3f a,vector3f b){
	vector3f c;
	c.x=a.x-b.x;
	c.y=a.y-b.y;
	c.z=a.z-b.z;
	return c;
}

vector3f smulp(vector3f a,float c){
	a.x=c*a.x;
	a.y=c*a.y;
	a.z=c*a.z;
	return a;
}

float dotproduct(vector3f a,vector3f b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

vector3f crossproduct(vector3f a,vector3f b){
	vector3f c;
	c.x=a.y*b.z-b.y*a.z;
	c.y=b.x*a.z-a.x*b.z;
	c.z=a.x*b.y-b.x*a.y;
	return c;
}

vector3f unitvec(vector3f a){
	vector3f c;
	float f=magnitude(a);
	c.x=a.x/f;
	c.y=a.y/f;
	c.z=a.z/f;
	return c;
}

vector3f setvalues(float x,float y,float z){
	vector3f v;
	v.x=x;
	v.y=y;
	v.z=z;
	return v;
}
