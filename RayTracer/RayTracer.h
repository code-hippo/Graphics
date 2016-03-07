#pragma once

#define MAXTRACEDEPTH	3

#include "Def.h"
#include "RenderTarget.h"
#include "Ray.h"
#include "Colour.h"

class Scene;
class Primitive;

class RayTracer
{
public:
	RayTracer(RenderTarget* renderTarget);
	~RayTracer();


	Scene* GetScene() { return mScene; };


	void	Initialize();
	Colour	TraceRay(Ray& ray, int traceDepth);
	void	Render();

protected:
	float			mViewPlaneX1, mViewPlaneX2, mViewPlaneY1, mViewPlaneY2;
	float			mDeltaX, mDeltaY;
	float			mCurrentX, mCurrentY;
	RenderTarget*	mRenderTarget;
	Scene*			mScene;
	int				mNextLine, mBufferIndex;
	Vector3f		mEyePosition;

};
