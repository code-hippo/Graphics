/*
 * read.h
 *
 *  Created on: Sep 13, 2014
 *      Author: bhargavvar
 */


#ifndef READ_H_
#define READ_H_

#include <iostream>
#include <vector>

using namespace std;

typedef vector<float> vector1;

float magnitude(vector1 a);
vector1 vsum(vector1 a,vector1 b);
vector1 vsub(vector1 a,vector1 b);
vector1 vscalarmult(vector1 a,float	 c);
float vdot(vector1 a,vector1 b);
vector1 vcross(vector1 a, vector1 b);
vector1 vunit(vector1 a);
vector1 vsetval(float x,float y,float z);
void split(string str,vector<float>& ans);


class UVN{
public:
	vector1 Ref;
	vector1 Eye;
	vector1 U;
	vector1 V;
	vector1 N;
	float near;
	float far;
	float wl,wr,wb,wt;
	vector1 wlt,wrt,wlb,wrb;

	void fileread1(void);
	UVN();
	~UVN();
};

UVN* load();


#endif
