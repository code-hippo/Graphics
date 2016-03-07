


#ifndef TEXTURe_H_
#define TEXTURE_H_
#include "readData.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/**
 * @brief to read textueID of the array
 * @param image image filename
 * @return int textureID
 */
GLuint readTexture(Image* image);


#endif /* TEXTURE_H_ */
