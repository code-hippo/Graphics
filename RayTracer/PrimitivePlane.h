#pragma once
#include "Primitive.h"


class PrimitivePlane : public Primitive
{
public:
	PrimitivePlane(Material material, Vector3f& normal, float distance, bool castsShadow = false)
		: Primitive(material, castsShadow){
			mNormal=(normal);
			mDistance=(distance); }
	~PrimitivePlane();

	Vector3f	GetNormal(Vector3f& position) { return mNormal; };


	bool Intersect(Ray& ray, float& distance)
	{
		bool result = false;



		float rayDotPlaneNormal = mNormal*ray.GetDirection();


		if (rayDotPlaneNormal < 0)
		{
			float distanceToIntersection = -((mNormal*ray.GetOrigin()) + mDistance) / rayDotPlaneNormal;
			if (distanceToIntersection < MAXDISTANCE)
			{
				distance = distanceToIntersection;
				result = true;
			}
		}

		return result;
	}
private:
	Vector3f mNormal;
	float	mDistance;
};
