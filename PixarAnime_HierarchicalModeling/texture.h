


#ifndef TEXTURe_H_
#define TEXTURE_H_
#include "readData.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLuint readTexture(Image* image);


#endif /* TEXTURE_H_ */
