/*
 * trans.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: bhargavvar
 */

#include "trans.h"
//#include "read.h"



using namespace std;


 void matmult(mat m1, mat m2){
 	GLint row, col;
 	mat temp;
 	for(row =0;row<4;row++){
 		for (col =0; col<4; col++){
 			temp[row][col]=m1[row][0]*m2[0][col]+
 					m1[row][1]*m2[1][col]+
 					m1[row][2]*m2[2][col]+
 					m1[row][3]*m2[3][col];
 		}
 	}
 	//m2=temp;
 	for(row =0;row<4;row++){
 			for (col =0; col<4; col++){
 				m2[row][col]=temp[row][col];
 			}
 	}
 }
 void matsetID(mat m1 ){
 	GLint row, col;
 		for(row =0;row<4;row++){
 			for (col =0; col<4; col++){
 				m1[row][col]=(row==col);
 			}
 		}
 }

 void trans3D(mat m1,vector1 trans ){
 	for(int i=0;i<3;i++){
 		m1[3][i]+=trans[i];
 	}
 }

 vector1 p_wcs_f_vcs( UVN* b,vector1 p){
 	vector1 ans=vector1(3,0);
 	ans[0]=p[0]*b->U[0]+p[1]*b->V[0]+p[2]*b->N[0] + b->Ref[0];
 	ans[1]=p[0]*b->U[1]+p[1]*b->V[1]+p[2]*b->N[1] + b->Ref[1];
 	ans[2]=p[0]*b->U[2]+p[1]*b->V[2]+p[2]*b->N[2] + b->Ref[2];
 	return ans;
 }

 vector1 dir_wcs_f_vcs(UVN* b,vector1 p){
 	vector1 ans=vector1(3,0);
 	ans[0]=p[0]*b->U[0]+p[1]*b->V[0]+p[2]*b->N[0] ;
 	ans[1]=p[0]*b->U[1]+p[1]*b->V[1]+p[2]*b->N[1] ;
 	ans[2]=p[0]*b->U[2]+p[1]*b->V[2]+p[2]*b->N[2] ;
 	return ans;
 }

 vector1 p_vcs_f_wcs(UVN* b,vector1 p){
 	vector1 ans=vector1(3,0);
 	ans[0]=(p[0]-b->Ref[0])*b->U[0]+(p[1]-b->Ref[1])*b->U[1]+(p[2]-b->Ref[2])*b->U[2];
 	ans[1]=(p[0]-b->Ref[0])*b->V[0]+(p[1]-b->Ref[1])*b->V[1]+(p[2]-b->Ref[2])*b->V[2];
 	ans[2]=(p[0]-b->Ref[0])*b->N[0]+(p[1]-b->Ref[1])*b->N[1]+(p[2]-b->Ref[2])*b->N[2];
 	return ans;
 }

 vector1 dir_vcs_f_wcs(UVN* b,vector1 p){
 	vector1 ans=vector1(3,0);
 	ans[0]=(p[0])*b->U[0]+(p[1])*b->U[1]+(p[2])*b->U[2];
 	ans[1]=(p[0])*b->V[0]+(p[1])*b->V[1]+(p[2])*b->V[2];
 	ans[2]=(p[0])*b->N[0]+(p[1])*b->N[1]+(p[2])*b->N[2];
 	return ans;
 }

 void compute_unit_VCS(UVN* _read){
	 _read->N=vscalarmult(_read->N,60.0/_read->far);
	 _read->U=vscalarmult(_read->U,30.0/_read->wr);
	 _read->V=vscalarmult(_read->V,30.0/_read->wt);
	// return p;
 }

 vector1 normal_vcs( UVN* b,vector1 p){

 }

 vector1 p_from_eye( vector1& wp,GLfloat d, vector1 eye){
 	vector1 proj_p=vunit(vsub(wp,eye));
 	return vsum(vscalarmult(proj_p,d),eye);
 }

 //mat v_w;
 //v_w[0][0]=VCS.U[0];
 //v_w[0][1]=VCS.U[1];
 //v_w[0][2]=VCS.U[2];
 //v_w[0][3]=0;
 //v_w[0][0]=VCS.V[0];
 //v_w[0][1]=VCS.V[0];
 //v_w[0][2]=VCS.V[0];
 //v_w[0][3]=0;
 //v_w[0][0]=VCS.N[0];
 //v_w[0][1]=VCS.N[0];
 //v_w[0][2]=VCS.N[0];
 //v_w[0][3]=0;
 //v_w[0][0]=0;
 //v_w[0][1]=0;
 //v_w[0][2]=0;
 //v_w[0][3]=0;



 void rotate3D(mat m1,vector1 r1){


 }
 void scale3D(mat m1,GLfloat sx,GLfloat sy,GLfloat sz,vector1 pt){

 }

//
//  int main(){
//
//     UVN  *p1=load() ;
//     p1->fileread1();
//     vector1 p=p1->U;
//     vector1 eye= p_wcs_f_vcs(p1,p1->Eye);
//     for(int i=0;i<(int)p1->Eye.size();i++){
//     	cout<< p[i] <<"t"<<endl;
//     }
//
// 	 return 0;
//  }
