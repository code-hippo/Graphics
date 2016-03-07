/*
 * Light.h
 *
 *  Created on: 18-Sep-2014
 *      Author: vignan_pc
 */


#pragma once

#include "Vector3f.h"
#include "Colour.h"
#include "Primitive.h"
class Light{
public:

	Light(Colour mcolour = Colour(),Vector3f mposition =Vector3f() )
		: mcolour(mcolour),mposition(mposition) {};

	~Light(void){};
	Colour		GetColour()	{ return mcolour; };
	Vector3f GetPosition(){return mposition;};

private:
	Colour mcolour;
	Vector3f mposition;
};



