/*
 * terrain.cpp
 *
 *  Created on: 12-Aug-2013
 *      Author: vignan_pc
 */



//converting image to array of information
#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>


#include "readData.h"
#include "vector3f.h"
#include"terrain.h"

using namespace std;


terrain::terrain(int length,int width){
	l=length;
	w=width;
	normals = new vector3f*[l];
	for(int i = 0; i < l; i++) {
		normals[i] = new vector3f[w];
	}
	hs=new float*[l];
	for(int i=0;i<l;i++){
		hs[i]=new float[w];
	}
	normalscomputed=false;
}

	//Deconstructor

terrain::~terrain(){
	for(int i = 0; i < l; i++) {
		delete[] hs[i];
	}
	delete[] hs;

	for(int i = 0; i < l; i++) {
		delete[] normals[i];
	}
	delete[] normals;
}

	//Functions on terrain class

int terrain::length(){
		return l;
}

int terrain::width(){
	return w;
}

void terrain::setHeight(int x, int z, float y) {
	hs[z][x] = y;
	normalscomputed = false;
}

// computing the normals at every (x,z)
void terrain::computeNormals() {
	if (normalscomputed) {
		return;
	}
	vector3f** param_norm = new vector3f*[l];
	for(int i = 0; i < l; i++) {
		param_norm[i] = new vector3f[w];
	}

		for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			vector3f avg=setvalues(0.0f, 0.0f, 0.0f);
			vector3f in,out,left,right;

			//computing in
			if (z < l - 1) {
				in = setvalues(0.0f, hs[z + 1][x] - hs[z][x], 1.0f);
			}
			////computing out
			if (z > 0) {
				out = setvalues(0.0f, hs[z - 1][x] - hs[z][x], -1.0f);
			}
			//computing left
			if (x > 0) {
				left =setvalues(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
			}

			//computing right
			if (x < w - 1) {
				right = setvalues(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
			}

			if (x > 0 && z > 0) {
				avg=sum(avg,unitvec(crossproduct(out,left)));
			}
			if (x > 0 && z < l - 1) {
				avg =sum(avg, unitvec(crossproduct(in,left)));
			}
			if (x < w - 1 && z < l - 1) {
				avg = sum(avg,unitvec(crossproduct(right,in)));
			}
			if (x < w - 1 && z > 0) {
				avg = sum(avg,unitvec(crossproduct(out,right)));
			}

			param_norm[z][x] = avg;
			}
	}


	float f=0.5;
	for(int z = 0; z < l; z++) {
		for(int x = 0; x < w; x++) {
			vector3f var = param_norm[z][x];

			if (x > 0) {
				var =sum(var, smulp(param_norm[z][x - 1],f));
			}
			if (x < w - 1) {
				var=sum (var,smulp(param_norm[z][x + 1],f) );
			}
			if (z > 0) {
				var= sum(var,smulp(param_norm[z - 1][x],f));
			}
			if (z < l - 1) {
				var= sum(var,smulp(param_norm[z + 1][x],f));
			}

			if (magnitude(var) == 0) {
				var= setvalues(0.0f, 1.0f, 0.0f);
			}
			normals[z][x] = var;
		}
	}
	for(int i = 0; i < l; i++) {
		delete[] param_norm[i];
	}
	delete[] param_norm;

	normalscomputed = true;
}

vector3f terrain::getNormal(int x, int z) {
	if (!normalscomputed) {
		computeNormals();
	}
	return normals[z][x];
}

float terrain::getHeight(int x,int z){
	return hs[z][x];
}

vector3f NormalAt(terrain* terrain, float x, float z) {
	//Make (x, z) lie within the bounds of the terrain
	if (x < 0) {
		x = 0;
	}
	else if (x > terrain->width() - 1) {
		x = terrain->width() - 1;
	}
	if (z < 0) {
		z = 0;
	}
	else if (z > terrain->length() - 1) {
		z = terrain->length() - 1;
	}

	//Compute the grid cell in which (x, z) lies and how close we are to the
	//left and outward edges
	int leftX = (int)x;
	if (leftX == terrain->width() - 1) {
		leftX--;
	}
	float fracX = x - leftX;

	int outZ = (int)z;
	if (outZ == terrain->width() - 1) {
		outZ--;
	}
	float fracZ = z - outZ;

	//Compute the four heights for the grid cell
	vector3f h11 = terrain->getNormal(leftX, outZ);
	vector3f h12 = terrain->getNormal(leftX, outZ + 1);
	vector3f h21 = terrain->getNormal(leftX + 1, outZ);
	vector3f h22 = terrain->getNormal(leftX + 1, outZ + 1);

	//Take a weighted average of the four heights
	return sum(smulp( sum( smulp(h11,(1 - fracZ)), smulp( h12,fracZ)),1-fracX) ,
			smulp( sum(smulp( h21,1-fracZ) , smulp(h22,fracZ)),fracX));
}

float heightAt(terrain* terrain, float x, float z) {
	//Make (x, z) lie within the bounds of the terrain
	if (x < 0) {
		x = 0;
	}
	else if (x > terrain->width() - 1) {
		x = terrain->width() - 1;
	}
	if (z < 0) {
		z = 0;
	}
	else if (z > terrain->length() - 1) {
		z = terrain->length() - 1;
	}

	//Compute the grid cell in which (x, z) lies and how close we are to the
	//left and outward edges
	int leftX = (int)x;
	if (leftX == terrain->width() - 1) {
		leftX--;
	}
	float fracX = x - leftX;

	int outZ = (int)z;
	if (outZ == terrain->width() - 1) {
		outZ--;
	}
	float fracZ = z - outZ;

	//Compute the four heights for the grid cell
	float h11 = terrain->getHeight(leftX, outZ);
	float h12 = terrain->getHeight(leftX, outZ + 1);
	float h21 = terrain->getHeight(leftX + 1, outZ);
	float h22 = terrain->getHeight(leftX + 1, outZ + 1);

	//Take a weighted average of the four heights
	return (1 - fracX) * ((1 - fracZ) * h11 + fracZ * h12) +
		fracX * ((1 - fracZ) * h21 + fracZ * h22);
}

terrain* createTerrain(const char* filename, float height) {
	Image* image = loadImage(filename);
	terrain* t = new terrain(image->width, image->height);
	for(int y = 0; y < image->height; y++) {
		for(int x = 0; x < image->width; x++) {
			unsigned char color =
				(unsigned char)image->pixels[3 * (y * image->width + x)];
			float h = height * ((color / 255.0f) - 0.5f);
			t->setHeight(x, y, h);
		}
	}

	delete image;
	t->computeNormals();
	return t;
}
