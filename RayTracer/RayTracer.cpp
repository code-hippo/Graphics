/*
 * RayTracer.cpp
 *
 *  Created on: 19-Sep-2014
 *      Author: vignan_pc
 */

#include "Def.h"
#include "RayTracer.h"
#include "Scene.h"
#include "Vector3f.h"


RayTracer::RayTracer(RenderTarget* renderTarget)
{
	mScene = new Scene();
	mRenderTarget = renderTarget;
}

RayTracer::~RayTracer()
{
	delete mScene;
}


void RayTracer::Initialize()
{
	// Reset current line and buffer (current pixel) index
	mNextLine = mBufferIndex = 0;

	// Camera/view position from which rays will be cast
	mEyePosition = Vector3f(0, 4, -5);

	// View plane in world coordinates (based on screen aspect ratio - 16:10)
	mViewPlaneX1 = -8;
	mViewPlaneX2 = 8;
	mViewPlaneY1 = mCurrentY = 5;
	mViewPlaneY2 = -5;


	mDeltaX = (mViewPlaneX2 - mViewPlaneX1) / mRenderTarget->GetWidth();
	mDeltaY = (mViewPlaneY2 - mViewPlaneY1) / mRenderTarget->GetHeight();
}

// ray tracing
Colour RayTracer::TraceRay(Ray& ray, int traceDepth)
{
	if (traceDepth > MAXTRACEDEPTH)
		return Colour();

	Colour		litColour, reflectedColour;
	float		distanceToIntersect = MAXDISTANCE;
	Vector3f		intersectionPoint;
	Primitive*	nearestPrimitive = 0;

	nearestPrimitive = mScene->GetFirstPrimitive(ray, distanceToIntersect);

	if (!nearestPrimitive)
		return Colour();

	else
	{
		// Ambient,Specular lighting
		intersectionPoint = ray.GetOrigin() + ray.GetDirection() * distanceToIntersect;
		litColour = mScene->CalculatePrimitiveLightingAtPoint((*nearestPrimitive), intersectionPoint, ray.GetDirection());

		//  reflection
		float reflectionFactor = nearestPrimitive->GetMaterial()->Reflection;

		if (reflectionFactor > 0.0f)
		{
			Vector3f normal = nearestPrimitive->GetNormal(intersectionPoint);
			Vector3f reflected = ray.GetDirection() - normal * (2.0f * (ray.GetDirection()*normal));

			Ray reflectedRay = Ray(intersectionPoint , reflected);
			reflectedColour = TraceRay(reflectedRay, traceDepth + 1) * reflectionFactor;
		}

		return litColour + reflectedColour;
	}
}


void RayTracer::Render()
{

	for (int y = 0; y < mRenderTarget->GetHeight(); y++)
	{

		mCurrentX = mViewPlaneX1;


		for (int x = 0; x < mRenderTarget->GetWidth(); x++)
		{

			Vector3f direction = Vector3f(mCurrentX, mCurrentY, 0) - mEyePosition;
			direction.Normalize();

			Ray ray(mEyePosition, direction);


			Colour pixelColour = TraceRay(ray, 1);


			mRenderTarget->SetPixel(mBufferIndex++, pixelColour.CreatePixel());


			mCurrentX += mDeltaX;
		}


		mCurrentY += mDeltaY;






	}


}
