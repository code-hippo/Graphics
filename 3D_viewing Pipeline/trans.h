/*
 * trans.h
 *
 *  Created on: Aug 27, 2014
 *      Author: bhargavvar
 */
#ifndef TRANS_H_
#define TRANS_H_


#include <GL/gl.h>
#include "read.h"
using namespace std;

typedef GLfloat mat[4][4];


void matmult(mat m1, mat m2);
void matsetID(mat m1 );
void trans3D(mat m1,vector1 trans );
void compute_unit_VCS(UVN* b);
vector1 normal_vcs( UVN* b,vector1 p);
vector1 p_wcs_f_vcs( UVN* b,vector1 p);
vector1 dir_wcs_f_vcs(UVN* b,vector1 p);
vector1 p_vcs_f_wcs(UVN* b,vector1 p);
vector1 dir_vcs_f_wcs(UVN* b,vector1 p);
vector1 p_from_eye(vector1& wp,GLfloat d, vector1 eye);
void rotate3D(mat m1,vector1 r1);
void scale3D(mat m1,GLfloat sx,GLfloat sy,GLfloat sz,vector1 pt);


#endif
