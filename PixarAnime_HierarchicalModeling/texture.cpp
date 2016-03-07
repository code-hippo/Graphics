/*
 * texturing.cpp
 *
 *  Created on: 13-Aug-2013
 *      Author: vignan_pc
 */


#include <GL/gl.h>

#include "texture.h"

GLuint readTexture(Image* image) {
	GLuint texturedata;
	glGenTextures(1, &texturedata);
	glBindTexture(GL_TEXTURE_2D, texturedata);
	//Mapping the image to the texture
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,
				 0,                            //The border of the image
				 GL_RGB, 					  //pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, 			  //GL_UNSIGNED_BYTE, because pixels are stored as unsigned numbers

				 image->pixels);             //pixel data
	return texturedata;						 //Returns the data of the texture
}


