///*
// * Colour.cpp
// *
// *  Created on: 19-Sep-2014
// *      Author: vignan_pc
// */
//
//
//#include "Colour.h"
//
//Colour::Colour()
//		: r(0), g(0), b(0) {};
//
//	Colour::Colour(float r, float g, float b)
//		: r(r), g(g), b(b) {};
//
//	Colour::Colour(const Colour& v)
//	{
//		r=v.r;
//		g=v.g;
//		b=v.b;
//	}
//
//	Colour::~Colour(void)
//	{
//	}
//
//
//	Colour Colour::	operator +	(const Colour& rhs)
//	{
//		return Colour(this->r+rhs.r,this->g+rhs.g,this->b+rhs.b);
//	}
//
//	Pixel Colour::CreatePixel()
//	{
//		int red   =	(int)(r * 256);
//		int green = (int)(g * 256);
//		int blue  =	(int)(b * 256);
//
//		if (red > 255)		red = 255;
//		if (green > 255)	green = 255;
//		if (blue > 255)		blue = 255;
//
//		return (red << 16) | (green << 8) | blue;
//	}
