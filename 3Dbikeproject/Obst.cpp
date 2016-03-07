/*
 * Obst.cpp
 *
 *  Created on: 09-Sep-2013
 *      Author: vignan_pc
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <set>
#include <sstream>
#include <stdlib.h>
#include <vector>
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / ((float) RAND_MAX +1);
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
/*vector3f* sai[10];
//vector3f* arraycreator(terrain* _terrain){
for(int i=0;i<10;i++){
	vector3f sa[10];
	sa[i]=RandomFloat((float)_terrain->width,(float)_terrain->length);
}}*/
class obst{

};

