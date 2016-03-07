/*
 * RenderTarget.h
 *
 *  Created on: 19-Sep-2014
 *      Author: vignan_pc
 */


#pragma once

#include "Def.h"

class RenderTarget
{
public:
	RenderTarget(int width, int height) :
		mWidth(width),
		mHeight(height)
	{
		mBuffer = new Pixel[width * height];

	};
	~RenderTarget(){
		delete [] mBuffer;
	};



	Pixel*		GetBuffer()		{ return mBuffer;	  };
	int			GetWidth()		{ return mWidth;	  };
	int			GetHeight()		{ return mHeight;	  };

	void SetPixel(int index, Pixel pixel)
	{
		mBuffer[index] = pixel;
	};
	void Clear(Pixel colour)
	{
		int pixelCount = mWidth * mHeight;

		for (int i = 0; i < pixelCount; i++)
		{
			mBuffer[i] = colour;
		}
	};
	Pixel*	mBuffer;

private:

	int		mWidth, mHeight;

};
