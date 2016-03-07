/*
 * Ray.h
 *
 *  Created on: 18-Sep-2014
 *      Author: vignan_pc
 */

#pragma once

#include "Vector3f.h"

class Ray
{
public:

	Ray():Origin(Vector3f(0,0,0)),
			Direction(Vector3f(0.0,0.0,0.0)){};

	Ray(Vector3f& origin, Vector3f& direction):
				Origin(origin),Direction(direction){}

	~Ray() {};

	Vector3f&	GetOrigin()		{ return Origin;	 };
	Vector3f&	GetDirection()	{ return Direction; };

private:
	Vector3f Origin;
	Vector3f Direction;

};




