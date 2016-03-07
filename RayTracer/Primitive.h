/*
 * Primitive.h
 *
 *  Created on: 19-Sep-2014
 *      Author: vignan_pc
 */


#pragma once
#include "Vector3f.h"
#include "Ray.h"
#include "Material.h"

class Primitive
{
public:

	Primitive(Material material, bool castsShadow = true)
		: mMaterial(material),
		mCastsShadow(castsShadow) {};
	 ~Primitive(void)
	{
	}


	bool			CastsShadow()				{ return mCastsShadow; };
	Material*		GetMaterial()				{ return &mMaterial; };
	virtual Colour	GetColour(Vector3f&)			{ return mMaterial.Diffuse; };
	virtual Vector3f GetNormal(Vector3f& position) = 0;


	virtual bool Intersect(Ray& ray, float& distance) = 0;
private:
	Material	mMaterial;
	bool		mCastsShadow;


};


