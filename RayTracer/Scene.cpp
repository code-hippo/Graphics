// --------------------------------------------------------------------------------
// Scene.cpp: Represents a collection of 3D primitives/lights. Calculates lighting.
// --------------------------------------------------------------------------------

#include "Scene.h"



Scene::Scene()
{
	SetupScene();
}

Scene::~Scene()
{
	for (unsigned int i = 0; i < mPrimitives.size(); i++)
		delete mPrimitives[i];

	for (unsigned int i = 0; i < mLights.size(); i++)
		delete mLights[i];

}


// Return the first primitive that intersects the given ray
Primitive* Scene::GetFirstPrimitive(Ray& ray, float& distanceToIntersect)
{
	Primitive*	nearestPrimitive = 0;
	float		distance = MAXDISTANCE;


	for (unsigned int p = 0; p < mPrimitives.size(); p++)
	{
		Primitive* currentPrimitive = mPrimitives[p];


		if (currentPrimitive->Intersect(ray, distance))
		{

			if ( distance < distanceToIntersect && distance > 0)
			{
				distanceToIntersect = distance;
				nearestPrimitive = currentPrimitive;
			}
		}
	}

	return nearestPrimitive;
}


Colour Scene::CalculatePrimitiveLightingAtPoint(Primitive& primitive, Vector3f& intersectionPoint, Vector3f rayDirection)
{
	Colour colourAtIntersect;


	for (unsigned int l = 0; l < mLights.size(); l++)
	{
		Light* light = mLights[l];



			Vector3f normal = primitive.GetNormal(intersectionPoint);
			Vector3f toLight = ((Light*)light)->GetPosition() - intersectionPoint;


			float distToLight = toLight.magnitude();
			toLight *= (1.0f / distToLight);


			bool inLight = true;
			Ray  shadowRay = Ray(intersectionPoint , toLight);

			for (unsigned int p = 0; p < mPrimitives.size(); p++)
			{
				Primitive* primitiveToTest = mPrimitives[p];


				if ( primitiveToTest->CastsShadow() )
				{
					if (primitiveToTest->Intersect(shadowRay, distToLight) )
					{
						inLight = false;
						break;
					}
				}
			}

			if (inLight)
			{

				float diffuseIntensity = (toLight*normal) * primitive.GetMaterial()->DiffuseFactor;


				if (diffuseIntensity > 0 )
				{
					colourAtIntersect += (primitive.GetMaterial()->Diffuse * light->GetColour()) * diffuseIntensity;
				}


				Vector3f reflectedLight = toLight - normal * (2.0f * (toLight*normal));
				float	reflectedLightAlongRay = (rayDirection*reflectedLight);


				if (reflectedLightAlongRay > 0 )
				{
					float specularIntensity = powf(reflectedLightAlongRay, 25) * primitive.GetMaterial()->Specular;
					colourAtIntersect += (light->GetColour() * specularIntensity);
				}
			}

	}

	return colourAtIntersect;
}


void Scene::SetupScene()
{

	mLights.push_back(new Light(
		Colour(1.0f, 1.0f, 1.0f),
		Vector3f(5.0f, 25.0f, 0.0f)));

	mLights.push_back(new Light(
			Colour(1.0f, 1.0f, 1.0f),
			Vector3f(-5.0f, 25.0f, 5.0f)));

	Vector3f * C4=new Vector3f(7.5f, 2.0f, 5.0f);

	mPrimitives.push_back(new PrimitiveSphere(
		Material(Colour(1.0f, 0.0f, 0.0f), 0.6f, 0.0f, 1.0f),
		*C4, 3.0f, false));
//

	Vector3f* c1=new Vector3f(-7.5, 2.0, 5.0);
	Vector3f* c5=new Vector3f(-0.0, 2.0, 7.5);
	Vector3f* c2=new Vector3f(0, 0, -1);
	Vector3f* c3=new Vector3f(0, 1, 0);
	Vector3f* c6=new Vector3f(1, 0, 0);
	mPrimitives.push_back(new PrimitiveSphere(
			Material(Colour(1.0f, 1.0f, 0.0f), 0.2f, 1.0f, 0.0f),
			*c5, 1.5f, true));
	mPrimitives.push_back(new PrimitiveSphere(
		Material(Colour(0.0f, 0.0f, 1.0f), 0.2f, 1.0f, 0.2f),
		*c1, 3.0f, true));


	mPrimitives.push_back(new PrimitivePlane(
		Material(Colour(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.2f),
		*c2, 10.0f, false));
//

	mPrimitives.push_back(new PrimitivePlane(
		Material(Colour(0.0,.3,1), 1.0f, 1.0f, 0.2f),
		*c3, 2.0f, false));

//	mPrimitives.push_back(new PrimitivePlane(
//			Material(Colour(0.0,0,1), 1.0f, 1.0f, 0.2f),
//			*c6, 15.0f, false));

}
