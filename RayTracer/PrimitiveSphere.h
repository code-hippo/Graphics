/*
 * PrimitiveSphere.h
 *
 *  Created on: 19-Sep-2014
 *      Author: vignan_pc
 */

#pragma once

#include "Primitive.h"
#include "Vector3f.h"

class PrimitiveSphere : public Primitive
{

public:
	PrimitiveSphere(Material material, Vector3f& center, float radius, bool castsShadow = true)
		: Primitive(material, castsShadow){
			mCenter=(center);
			mRadiusSquared=(radius * radius);
			mRadius=(radius);
			mOneOverRadius=(1.0f/ radius) ;}
	 ~PrimitiveSphere(void);


	Vector3f&	GetCenter()					 { return mCenter; };
	Vector3f	GetNormal(Vector3f& position) { return (position - mCenter) * mOneOverRadius; };


	bool Intersect(Ray& ray, float& distance)
	{
		bool result = false;


		Vector3f e = mCenter - ray.GetOrigin();
		float	a = e*ray.GetDirection();

		float f = mRadiusSquared - (e*e) + (a * a);

		if (f < 0.0f)
	        {return result;}

		else
		{
			float t = a - sqrtf(f);

			if (t > 0.1f && t < MAXDISTANCE)
			{
				distance = t;
				result = true;
			}
		}

	    return result;
	}

private:
	Vector3f mCenter;
	float mRadius;
	float mRadiusSquared;
	float mOneOverRadius;
};


