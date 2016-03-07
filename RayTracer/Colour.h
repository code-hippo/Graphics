/*
 * Colour.h
 *
 *  Created on: 18-Sep-2014
 *      Author: vignan_pc
 */

#pragma once

#include "Def.h"


class Colour{
public:
	struct { float r, g, b; };
	Colour(void)
		: r(0), g(0), b(0) {};

	Colour(float r, float g, float b)
		: r(r), g(g), b(b) {};

	Colour(const Colour& v)
	{
		r=v.r;
		g=v.g;
		b=v.b;
	}

	~Colour(void)
	{
	}


	Colour operator +	(const Colour& rhs)
	{
		return Colour(this->r+rhs.r,this->g+rhs.g,this->b+rhs.b);
	}

	void operator +=	(const Colour& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
	}
	Colour operator *  (const Colour& rhs)
	{
		return Colour(r * rhs.r, g * rhs.g, b * rhs.b);
	}

	Colour operator *	(float scalar)
	{
		return Colour(r * scalar, g * scalar, b * scalar);
	}
	void operator *=	(float scalar)
	{
		r *= scalar;
		g *= scalar;
		b *= scalar;
	}
	Pixel CreatePixel()
	{
		int red   =	(int)(r * 256);
		int green = (int)(g * 256);
		int blue  =	(int)(b * 256);

		if (red > 255)		red = 255;
		if (green > 255)	green = 255;
		if (blue > 255)		blue = 255;

		return (red << 16) | (green << 8) | blue;
	}
};
