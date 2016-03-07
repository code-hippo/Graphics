/*

 *
 *  Created on: 12-Aug-2013
 *      Author: vignan_pc
 */

#ifndef VECTOR3F_H_
#define VECTOR3F_H_

/**
 * @brief vector construction
 */
typedef struct{
	float x;
	float y;
	float z;
}vector3f;

/**
 * @brief calculates magnitude
 * @param a vector magnitude to calculate
 * @return magnitude of vector a
 */
float magnitude(vector3f a);
/**
 * @brief sumof two vectors
 * @param a vector 1
 * @param b vector 2
 * @return sum vector
 */
vector3f sum(vector3f a,vector3f b);
/**
 * @brief subtraction of vectors
 * @param a vector 1
 * @param b vector 2
 * @return subtraction vector of 1 from 2
 */
vector3f sub(vector3f a,vector3f b);
/**
 * @brief sclar multiplier
 * @param a vector a
 * @param c scale
 * @return vector multiplied by the scale
 */
vector3f smulp(vector3f a,float c);
/**
 * @brief dotproduct of vectors
 * @param a vector 1
 * @param b vector 2
 * @return dotproduct of 1 and 2
 */
float dotproduct(vector3f a,vector3f b);
/**
 * @brief crossproduct of vectors
 * @param a vector 1
 * @param b vector 2
 * @return 1 and 2 cross products
 */
vector3f crossproduct(vector3f a,vector3f b);
/**
 * @brief unit vector taking
 * @param a vector to normalise
 * @return nomalised vector
 */
vector3f unitvec(vector3f a);
/**
 * @brief taking vector from components
 * @param x component x
 * @param y component y
 * @param z component z
 * @return vector with the x, y, z components
 */
vector3f setvalues(float x,float y,float z);
#endif /* VECTOR3F_H_ */
