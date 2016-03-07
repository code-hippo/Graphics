/*
 * terrain.h
 *
 *  Created on: Aug 17, 2013
 *      Author: vignan
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_
#include "vector3f.h"

/**
 * @brief class that handles terrain drawing
 */
class terrain{
public:

	//class variables
/**
 * @brief lenth of terrain
 */
	int l;
	/**
	 * @brief width of the terrain
	 */
	int w;
	/**
	 * @brief normals mapping in x,z coords
	 */
	vector3f** normals;
	/**
	 * @brief height mappping in x,z coords
	 */
	float** hs;
	//two dimensional array to store height at every point
	/**
	 * @brief whether normal is computed at x, z
	 */
	bool normalscomputed;  //to check whether normals are upto date

public:
	/**
	 * @brief terrain constructor
	 * @param length length of terrrain input
	 * @param width width of the terrain input
	 */
	terrain(int length,int width);
	/**
	 * @brief terrain class destructor
	 */
	~terrain();
	/**
	 * @brief length calculating func
	 * @return length of terrain
	 */
	int length();
	/**
	 * @brief width calculating func
	 * @return width of terrain
	 */
	int width();
	/**
	 * @brief to set height based on inputs
	 * @param x x input
	 * @param z y input
	 * @param y x input
	 */
	void setHeight(int x, int z, float y);
	/**
	 * @brief function to computer normals
	 */
	void computeNormals();
	/**
	 * @brief to return normal at x , z
	 * @param x x coord
	 * @param z z coord
	 * @return normal vector
	 */
	vector3f getNormal(int x, int z);
	/**
	 * @brief to return height at x,z
	 * @param x x coord
	 * @param z z coord
	 * @return height
	 */
	float getHeight(int x,int z);

};
/**
 * @brief creates terrain from th image and maxheight given
 * @param filename name of imagefile
 * @param height maxheight given
 * @return the terrain
 */
	terrain* createTerrain(const char* filename, float height);
	/**
	 * @brief cleans the memory of garbage
	 */
	void clean();
	/**
	 * @brief rendering inputs of terrain
	 */
	void initRendering();
	/**
	 * @brief to handle keyboard inputs
	 * @param key key pressed
	 * @param x mouse x postion
	 * @param y mouse y pposition
	 */
	void handleKeypress(unsigned char key, int x, int y);
	/**
	 * @brief draw the terrain in glut
	 */
	void drawScene();
	/**
	 * @brief to adjust window size
	 * @param w width of terrain
	 * @param h height of terrain
	 */
	void handleResize(int w, int h);
	/**
	 * @brief returns height at x,z of terrain
	 * @param t terrain
	 * @param x terrain x
	 * @param z terrain z
	 * @return height at terrain x,z
	 */
    float heightAt(terrain* t,float x,float z);
    /**
    	 * @brief returns normal at x,z of terrain
    	 * @param t terrain
    	 * @param x terrain x
    	 * @param z terrain z
    	 * @return normal at terrain x,z
    	 */

    vector3f NormalAt(terrain* t,float x,float z);

#endif /* TERRAIN_H_ */
