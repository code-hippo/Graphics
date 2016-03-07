/*
 * glm.h
 *
 *  Created on: Sep 19, 2014
 *      Author: bhargavvar
 */

#ifndef GLM_H
#define GLM_H

/*
      glm.h
      Nate Robins, 1997, 2000
      nate@pobox.com, http://www.pobox.com/~nate

      Wavefront OBJ model file format reader/writer/manipulator.

      Includes routines for generating smooth normals with
      preservation of edges, welding redundant vertices & texture
      coordinate generation (spheremap and planar projections) + more.

 */


//#include <GL/glut.h>
#include <GL/gl.h>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#define GLM_NONE     (0)            /* render with only vertices */
#define GLM_FLAT     (1 << 0)       /* render with facet normals */
#define GLM_SMOOTH   (1 << 1)       /* render with vertex normals */
#define GLM_TEXTURE  (1 << 2)       /* render with texture coords */
#define GLM_COLOR    (1 << 3)       /* render with colors */
#define GLM_MATERIAL (1 << 4)       /* render with materials */


/* GLMmaterial: Structure that defines a material in a model.
 */
typedef struct _GLMmaterial
{
//    char* name;                   /* name of material */
    float diffuse[4];           /* diffuse component */
    float ambient[4];           /* ambient component */
    float specular[4];          /* specular component */
    float emmissive[4];         /* emmissive component */
    float shininess;            /* specular exponent */
    float Ni;
    char*             name;           /* name of this group */
	int            numtriangles;   /* number of triangles in this group */
	int            numspheres;
	int            numplanes;
	int*           triangles;/* array of triangle indices */
	int*           spheres;
	int*           planes;
	struct _GLMmaterial* next;
} GLMmaterial;

/* GLMtriangle: Structure that defines a triangle in a model.
 */
typedef struct _GLMtriangle {
    float vertex1[3];float vertex2[3];float vertex3[3];           /* array of triangle vertex indices */
    float normal1[3];float normal2[3];float normal3[3];           /* array of triangle normal indices */
   // int tindices[3];           /* array of triangle texcoord indices*/
   //  int findex;                /* index of triangle facet normal */
} GLMtriangle;
typedef struct _GLMsphere {
    float centre[3];           /* array of triangle vertex indices */
    GLint radius;           /* array of triangle normal indices */
    //int tindices[3];           /* array of triangle texcoord indices*/
   // int findex;                /* index of triangle facet normal */
} GLMsphere;
typedef struct _GLMplane {
    float centre[3];           /* array of triangle vertex indices */
    float normal[3];           /* array of triangle normal indices */
    //int tindices[3];           /* array of triangle texcoord indices*/
    //int findex;                /* index of triangle facet normal */
} GLMplane;

/* GLMmodel: Structure that defines a model.
 */
typedef struct _GLMmodel {
    char*        pathname;            /* path to this model */

    int       numspheres;       /* number of facetnorms in model */
    GLMsphere*   spheres;          /* array of facetnorms */

    int       numtriangles;    /* number of triangles in model */
    GLMtriangle* triangles;       /* array of triangles */

    int       numplanes;    /* number of materials in model */
    GLMplane*    planes;       /* array of materials */

    int       nummaterials;    /* number of materials in model */
	GLMmaterial*    materials;       /* array of materials */

    float      position[3];          /* position of the model */

} GLMmodel;

GLMmaterial*
        _glmFindMaterial(GLMmodel* model, char* name);
GLvoid
        glmDelete(GLMmodel* model);

/* glmReadOBJ: Reads a model description from a Wavefront .OBJ file.
 * Returns a pointer to the created object which should be free'd with
 * glmDelete().
 *
 * filename - name of the file containing the Wavefront .OBJ format data.
 */
GLMmodel*
        glmReadOBJ(char* filename);



/* glmDraw: Renders the model to the current OpenGL context using the
 * mode specified.
 *
 * model    - initialized GLMmodel structure
 * mode     - a bitwise OR of values describing what is to be rendered.
 *            GLM_NONE    -  render with only vertices
 *            GLM_FLAT    -  render with facet normals
 *            GLM_SMOOTH  -  render with vertex normals
 *            GLM_TEXTURE -  render with texture coords
 *            GLM_FLAT and GLM_SMOOTH should not both be specified.
 */
GLvoid
		glmDraw(GLMmodel* model, int mode);

#endif // GLM_H
