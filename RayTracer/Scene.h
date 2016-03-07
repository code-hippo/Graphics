
#pragma once

#include <vector>
#include "Def.h"
#include "RayTracer.h"
#include "Primitive.h"
#include "PrimitiveSphere.h"
#include "PrimitivePlane.h"
#include "Light.h"

class Scene
{
public:
	Scene();
	~Scene();


	int			GetPrimitiveCount()	{ return mPrimitives.size(); };
	Primitive*	GetPrimitive(int i)	{ return mPrimitives[i];	 };


	Primitive*	GetFirstPrimitive(Ray& ray, float& distanceToIntersect);
	Colour		CalculatePrimitiveLightingAtPoint(Primitive& primitive, Vector3f& intersectionPoint, Vector3f rayDirection);

public:
	std::vector<Primitive*> mPrimitives;
	std::vector<Light*>		mLights;


	void SetupScene();
};
