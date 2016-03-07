/*
 * glm.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: bhargavvar
 */

/* includes */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cstdlib> // Added by dragly
#include "fileread.h"


/* defines */
#define T(x) model->triangles[(x)]
#define S(x) model->spheres[(x)]
#define P(x) model->planes[(x)]

GLMmaterial*
        _glmAddMaterial(GLMmodel* model, char* name)
{
    GLMmaterial* group;

    group = _glmFindMaterial(model, name);
    if (!group) {
        group = (GLMmaterial*)malloc(sizeof(GLMmaterial));
        group->name = strdup(name);
      //  group->material = 0;
        group->numtriangles = 0;
        group->triangles = NULL;
        group->numplanes = 0;
        group->planes = NULL;
		group->numspheres = 0;
		group->spheres = NULL;
        group->next = model->materials;
        model->materials = group;
        model->nummaterials++;
    }

    return group;
}

GLMmaterial*
        _glmFindMaterial(GLMmodel* model, char* name)
{
    GLMmaterial* group;

    assert(model);

    group = model->materials;
    while(group) {
        if (!strcmp(name, group->name))
            break;
        group = group->next;
    }

    return group;
}

static GLvoid
        _glmReadMTL(GLMmodel* model, char* name)
{
    FILE* file;

    char* filename;
    char  buf[128];
    int nummaterials, i;

    filename = (char*)malloc(sizeof(char) * ( strlen(name) + 1));
    strcpy(filename, name);
    model->pathname=strdup(name);

    /* open the file */
    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "_glmReadMTL() failed: can't open material file \"%s\".\n",
                filename);
        exit(1);
    }
    free(filename);

    /* count the number of materials in the file */
    nummaterials = 1;
    while(fscanf(file, "%s", buf) != EOF) {
        switch(buf[0]) {
        case '#':				/* comment */
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            break;
        case 'n':				/* newmtl */
            fgets(buf, sizeof(buf), file);
            nummaterials++;
            sscanf(buf, "%s %s", buf, buf);
            break;
        default:
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            break;
        }
    }

    rewind(file);

    /* allocate memory for the materials */
    model->materials = (GLMmaterial*)malloc(sizeof(GLMmaterial) * nummaterials);
    model->nummaterials = nummaterials;

    /* set the default material */
    for (i = 0; i < nummaterials; i++) {
        model->materials[i].name = NULL;
        model->materials[i].shininess = 0;
        model->materials[i].diffuse[0] = 0.8;
        model->materials[i].diffuse[1] = 0.8;
        model->materials[i].diffuse[2] = 0.8;
        model->materials[i].diffuse[3] = 1.0;
        model->materials[i].ambient[0] = 0.2;
        model->materials[i].ambient[1] = 0.2;
        model->materials[i].ambient[2] = 0.2;
        model->materials[i].ambient[3] = 1.0;
        model->materials[i].specular[0] = 0.0;
        model->materials[i].specular[1] = 0.0;
        model->materials[i].specular[2] = 0.0;
        model->materials[i].specular[3] = 1.0;
        model->materials[i].numtriangles=0;
        model->materials[i].numplanes=0;
        model->materials[i].numspheres=0;
        model->materials[i].triangles=NULL;
		model->materials[i].planes=NULL;
		model->materials[i].spheres=NULL;
    }
    model->materials[0].name = strdup("default");

    /* now, read in the data */
    nummaterials = 0;
    while(fscanf(file, "%s", buf) != EOF) {
        switch(buf[0]) {
        case '#':				/* comment */
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            break;
        case 'n':				/* newmtl */
            fgets(buf, sizeof(buf), file);
            sscanf(buf, "%s %s", buf, buf);
            nummaterials++;
            model->materials[nummaterials].name = strdup(buf);
            break;
        case 'S':				/* newmtl */
        	fgets(buf, sizeof(buf), file);
        	model->materials[nummaterials].numspheres++;
        	model->numspheres++;
            break;
        case 'T':				/* newmtl */
        	fgets(buf, sizeof(buf), file);
        	model->materials[nummaterials].numplanes++;
        	model->numplanes++;
            break;
        case 'P':				/* newmtl */
        	fgets(buf, sizeof(buf), file);
        	model->materials[nummaterials].numtriangles++;
        	model->numtriangles++;
            break;

        case 'N':
        	switch(buf[1]) {
			case 's':
				fscanf(file, "%f", &model->materials[nummaterials].shininess);
				/* wavefront shininess is from [0, 1000], so scale for OpenGL */
				model->materials[nummaterials].shininess /= 1000.0;
				model->materials[nummaterials].shininess *= 128.0;
				break;
			case 'i':
				fscanf(file, "%f", &model->materials[nummaterials].Ni);
				/* wavefront shininess is from [0, 1000], so scale for OpenGL */
				break;
        	}
        	break;

        case 'K':
            switch(buf[1]) {
            case 'd':
                fscanf(file, "%f %f %f",
                       &model->materials[nummaterials].diffuse[0],
                       &model->materials[nummaterials].diffuse[1],
                       &model->materials[nummaterials].diffuse[2]);
                break;
            case 's':
                fscanf(file, "%f %f %f",
                       &model->materials[nummaterials].specular[0],
                       &model->materials[nummaterials].specular[1],
                       &model->materials[nummaterials].specular[2]);
                break;
            case 'a':
                fscanf(file, "%f %f %f",
                       &model->materials[nummaterials].ambient[0],
                       &model->materials[nummaterials].ambient[1],
                       &model->materials[nummaterials].ambient[2]);
                break;
            default:
                /* eat up rest of line */
                fgets(buf, sizeof(buf), file);
                break;
            }
            break;
    default:
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            break;
        }
    }
    rewind(file);
    model->triangles = (GLMtriangle*)malloc(sizeof(GLMtriangle) * (model->numtriangles+1));
    model->planes = (GLMplane*)malloc(sizeof(GLMplane) * (model->numspheres+1));
    model->spheres = (GLMsphere*)malloc(sizeof(GLMsphere) * (model->numplanes+1));



    /* allocate memory for each case */
    for (i = 0; i < nummaterials; i++) {


        model->materials[i].triangles=(int*)malloc(sizeof(int) * model->materials[i].numtriangles);
		model->materials[i].planes=(int*)malloc(sizeof(int) * model->materials[i].numplanes);
		model->materials[i].spheres=(int*)malloc(sizeof(int) * model->materials[i].numspheres);
    }


    /* now, read in the data */
    nummaterials = -1;
    int numspheres=0;
    int numtriangles=0;
    int numplanes=0;
    while(fscanf(file, "%s", buf) != EOF) {
    	int si=0;int sp=0;int st=0;
           switch(buf[0]) {
           case 'n':				/* newmtl */
               fgets(buf, sizeof(buf), file);
               sscanf(buf, "%s %s", buf, buf);
               nummaterials++;

               break;
           case 'S':/* newmtl */
        	   fscanf(file, "%f %f %f",
				   &model->spheres[numspheres].centre[0],
				   &model->spheres[numspheres].centre[1],
				   &model->spheres[numspheres].centre[2]);
        	   model->materials[nummaterials].spheres[si]=numspheres;
        	   si++;
        	   numspheres++;
               break;

           case 'T':		/* newmtl */
        	   fscanf(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
				   &model->triangles[numtriangles].vertex1[0],&model->triangles[numtriangles].vertex1[1],&model->triangles[numtriangles].vertex1[2],
				   &model->triangles[numtriangles].vertex2[0],&model->triangles[numtriangles].vertex2[1],&model->triangles[numtriangles].vertex2[2],
				   &model->triangles[numtriangles].vertex3[0],&model->triangles[numtriangles].vertex3[1],&model->triangles[numtriangles].vertex3[2],
				   &model->triangles[numtriangles].normal1[0],&model->triangles[numtriangles].normal1[1],&model->triangles[numtriangles].normal1[2],
				   &model->triangles[numtriangles].normal3[0],&model->triangles[numtriangles].normal2[1],&model->triangles[numtriangles].normal2[2],
				   &model->triangles[numtriangles].normal3[0],&model->triangles[numtriangles].normal3[1],&model->triangles[numtriangles].normal3[2]);
        	   model->materials[nummaterials].triangles[st]=numtriangles;
        	   st++;
        	   numtriangles++;

               break;
           case 'P':				/* newmtl */
        	   fscanf(file, "%f %f %f %f %f %f",
				   &model->planes[numspheres].centre[0],
				   &model->planes[numspheres].centre[1],
				   &model->planes[numspheres].centre[2],
				   &model->planes[numspheres].normal[0],
				   &model->planes[numspheres].normal[1],
				   &model->planes[numspheres].normal[2]);
        	   model->materials[nummaterials].spheres[sp]=numplanes;
        	   sp++;
        	   numplanes++;
               break;
           default:
			   /* eat up rest of line */
			   fgets(buf, sizeof(buf), file);
			   break;
		   }
    }

}


GLvoid
        glmDelete(GLMmodel* model)
{
    GLMmaterial* group;
    int i;

    assert(model);

    if (model->pathname)   free(model->pathname);
    if (model->triangles)   free(model->triangles);
    if (model->planes)    free(model->planes);
    if (model->spheres)  free(model->spheres);
    if (model->materials) {
        for (i = 0; i < model->nummaterials; i++)
            free(model->materials[i].name);
    }
    while(model->materials) {
        group = model->materials;
        model->materials = model->materials->next;
        free(group->name);
        free(group->triangles);
        free(group->planes);
        free(group->spheres);
    }

    free(model);
}

/* glmReadOBJ: Reads a model description from a Wavefront .OBJ file.
 * Returns a pointer to the created object which should be free'd with
 * glmDelete().
 *
 * filename - name of the file containing the Wavefront .OBJ format data.
 */
GLMmodel*
        glmReadOBJ(char* filename)
{

    GLMmodel* model;
    FILE*     file;

    /* open the file */
    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "glmReadOBJ() failed: can't open data file \"%s\".\n",
                filename);
        exit(1);
    }

#if 0
    /* announce the model name */
    printf("Model: %s\n", filename);
#endif

    /* allocate a new model */
    model = (GLMmodel*)malloc(sizeof(GLMmodel));
    model->pathname      = strdup(filename);
    model->numtriangles   = 0;
    model->triangles      = NULL;
    model->numplanes    = 0;
    model->planes       = NULL;
    model->numspheres  = 0;
    model->spheres     = NULL;
    model->nummaterials  = 0;
    model->materials     = NULL;
    model->position[0]   = 0.0;
    model->position[1]   = 0.0;
    model->position[2]   = 0.0;

    /* make a first pass through the file to get a count of the number
     of vertices, normals, texcoords & triangles */

    /* allocate memory */

    _glmReadMTL(model, filename);

    /* close the file */
    fclose(file);

    return model;
}




/* glmDraw: Renders the model to the current OpenGL context using the
 * mode specified.
 *
 * model    - initialized GLMmodel structure
 * mode     - a bitwise OR of values describing what is to be rendered.
 *            GLM_NONE     -  render with only vertices
 *            GLM_FLAT     -  render with facet normals
 *            GLM_SMOOTH   -  render with vertex normals
 *            GLM_TEXTURE  -  render with texture coords
 *            GLM_COLOR    -  render with colors (color material)
 *            GLM_MATERIAL -  render with materials
 *            GLM_COLOR and GLM_MATERIAL should not both be specified.
 *            GLM_FLAT and GLM_SMOOTH should not both be specified.
 */
//GLvoid glmDraw(GLMmodel* model, int mode)
//{
// int i;
// GLMgroup* group;
//  assert(model);
// assert(model->vertices);
////  /* do a bit of warning */
// if (mode & GLM_FLAT && !model->facetnorms) {
//    printf("glmDraw() warning: flat render mode requested "
//          "with no facet normals defined.\n");
//    mode &= ~GLM_FLAT;
// }
// if (mode & GLM_SMOOTH && !model->normals) {
//   printf("glmDraw() warning: smooth render mode requested "
//          "with no normals defined.\n");
//    mode &= ~GLM_SMOOTH;
//  }
//  if (mode & GLM_TEXTURE && !model->texcoords) {
//    printf("glmDraw() warning: texture render mode requested "
//           "with no texture coordinates defined.\n");
//   mode &= ~GLM_TEXTURE;
//  }
//  if (mode & GLM_FLAT && mode & GLM_SMOOTH) {
//   printf("glmDraw() warning: flat render mode requested "
//           "and smooth render mode requested (using smooth).\n");
//    mode &= ~GLM_FLAT;
//  }
//  if (mode & GLM_COLOR && !model->materials) {
//    printf("glmDraw() warning: color render mode requested "
//           "with no materials defined.\n");
//    mode &= ~GLM_COLOR;
//  }
//  if (mode & GLM_MATERIAL && !model->materials) {
//    printf("glmDraw() warning: material render mode requested "
//           "with no materials defined.\n");
//   mode &= ~GLM_MATERIAL;
//  }
//  if (mode & GLM_COLOR && mode & GLM_MATERIAL) {
//    printf("glmDraw() warning: color and material render mode requested "
//          "using only material mode\n");
//    mode &= ~GLM_COLOR;
//  }
//  if (mode & GLM_COLOR)
//    glEnable(GL_COLOR_MATERIAL);
//  if (mode & GLM_MATERIAL)
//    glDisable(GL_COLOR_MATERIAL);
//
//  glPushMatrix();
//  glTranslatef(model->position[0], model->position[1], model->position[2]);
// glScalef(.02,.02,.02);
// glBegin(GL_TRIANGLES);
//  group = model->groups;
// while (group) {
//    if (mode & GLM_MATERIAL) {
//      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
//                   model->materials[group->material].ambient);
//      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
//                   model->materials[group->material].diffuse);
//     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
//                   model->materials[group->material].specular);
//       glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,
//                  model->materials[group->material].shininess);
//    }
//   if (mode & GLM_COLOR) {
//      glColor3fv(model->materials[group->material].diffuse);
//    }
//
//   for (i = 0; i < group->numtriangles; i++) {
//     if (mode & GLM_FLAT)
//       glNormal3fv(&model->facetnorms[3 * T(group->triangles[i]).findex]);
//
//     if (mode & GLM_SMOOTH)
//        glNormal3fv(&model->normals[3 * T(group->triangles[i]).nindices[0]]);
//      if (mode & GLM_TEXTURE)
//       glTexCoord2fv(&model->texcoords[2*T(group->triangles[i]).tindices[0]]);
//      glVertex3fv(&model->vertices[3 * T(group->triangles[i]).vindices[0]]);
//#if 0
//      printf("%f %f %f\n",
//            model->vertices[3 * T(group->triangles[i]).vindices[0] + X],
//            model->vertices[3 * T(group->triangles[i]).vindices[0] + Y],
//             model->vertices[3 * T(group->triangles[i]).vindices[0] + Z]);
//#endif
//
//      if (mode & GLM_SMOOTH)
//        glNormal3fv(&model->normals[3 * T(group->triangles[i]).nindices[1]]);
//     if (mode & GLM_TEXTURE)
//       glTexCoord2fv(&model->texcoords[2*T(group->triangles[i]).tindices[1]]);
//      glVertex3fv(&model->vertices[3 * T(group->triangles[i]).vindices[1]]);
//#if 0
//      printf("%f %f %f\n",
//             model->vertices[3 * T(group->triangles[i]).vindices[1] + X],
//            model->vertices[3 * T(group->triangles[i]).vindices[1] + Y],
//            model->vertices[3 * T(group->triangles[i]).vindices[1] + Z]);
//#endif
//
//      if (mode & GLM_SMOOTH)
//        glNormal3fv(&model->normals[3 * T(group->triangles[i]).nindices[2]]);
//      if (mode & GLM_TEXTURE)
//        glTexCoord2fv(&model->texcoords[2*T(group->triangles[i]).tindices[2]]);
//      glVertex3fv(&model->vertices[3 * T(group->triangles[i]).vindices[2]]);
//#if 0
//      printf("%f %f %f\n",
//             model->vertices[3 * T(group->triangles[i]).vindices[2] + X],
//             model->vertices[3 * T(group->triangles[i]).vindices[2] + Y],
//             model->vertices[3 * T(group->triangles[i]).vindices[2] + Z]);
//#endif
//
//    }
//
//    group = group->next;
//  }
//  glEnd();
//
//  glPopMatrix();
//}
