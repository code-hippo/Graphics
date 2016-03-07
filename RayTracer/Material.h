/*
 * material.h
 *
 *  Created on: 18-Sep-2014
 *      Author: vignan_pc
 */

#pragma once

#include "Colour.h"

struct Material
{
	// Fields
	Colour	Diffuse;
	float	DiffuseFactor;
	float	Reflection;
	float	Specular;


	// Default constructor
	Material(
		Colour diffuse = Colour(),
		float diffuseFactor = 0.9f,
		float reflection = 0.5f,
		float specular = 0.5f)

		: Diffuse(diffuse),
		DiffuseFactor(diffuseFactor),
		Reflection(reflection),
		Specular(specular) {};
};



