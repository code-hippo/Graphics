/*
 * physics.h
 *
 *  Created on: Aug 17, 2013
 *      Author: bhargavvar
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_
#endif /* PHYSICS_H_ */
/*
 * physics.h
 *
 *  Created on: Aug 12, 2013
 *      Author: bhargavvar
 */

#include "vector3f.h"
#include "terrain.h"
#include "glm.h"

//bike object related data and functions
/**
 * @brief Object is the class for bike and physics unification.
 * @details it takes in terrain and model and applies physics to bike.
 * @return void
 */
class Object
{
public:
	terrain* _terrain;
	float terrainlfactor;
	GLMmodel* _model;
/**
 * @brief used to smooth out game by time accumulation concept of rendering
 */
    float timeaccumulator;
   /**
    * @brief indicates position of object
    */
	vector3f pos;
/**
 * @brief indicates velocity vector of object
 */
	vector3f velocity;

/**
 * @brief used to return velocity in x
 * @return velocity in x
 */

	float velocityinX();
/**
 * @brief to set velocity in x
 * @param v velocity to set value
 */
	void setVelocityX(float v);

	/**
	 * @brief used to return velocity in y
	 * @return velocity in y
	 */
	float velocityinY();

	/**
	 * @brief to set velocity in y
	 * @param v velocity to set value
	 */
	void setVelocityY(float v);

	/**
	 * @brief used to return velocity in z
	 * @return velocity in z
	 */
	float velocityinZ();

	/**
	 * @brief to set velocity in z
	 * @param v velocity to set value
	 */
	void setVelocityZ(float v);

	/**
	* @brief acceleration vector
	*/
	vector3f accelerate;

	/**
 	*@brief  brief bike angle in counter clock with negative z
 	*/
	float bikeangle;

/**
 * @brief used to position cbehind the object
 * @return vector between object and camera
 */
	vector3f glulookat();

	/**
	 * @brief to find out position of object on terrain
	 * @return vector position of object on terrain on map
	 */
	vector3f posonterrain();

  /**
   *@brief  gives the size scale used on object
   */
    float size0;

		/**
 		* @brief to find whether on border of terrain
 		*/
		bool onterrainborder;

		/**
    * @brief function to render the game smooth
    */
		void timeaccumulatorfunc();
		/**
	 	*@brief  constructor for class
	 	* @param terrain terrain used
	 	* @param model object model used
	 	*/
		Object(terrain* terrain,GLMmodel* model);

		/**
 		*@brief  destructor
 		*/
		~Object();
		/**
 * @brief bike angle update function
 * @param dt time difference
 */
  void bikeangleupdate(float dt);
    /**
     *@brief  position update func
     * @param dt time diff
     */
	void posupdate(float dt);
	/**
	 * @brief velocity update func
	 * @param dt time diff
	 */
	void velupdate(float dt);
   /**
    *@brief  to calculate time and summed up physics upadte
    * @param dt time diff
    */
	void framestime(float dt);
	/**
	 *@brief  drawing the object
	 */
	void draw();
	/**
 	* @brief to use keyoperations on object position
 	*/
	void keyoperations();



	/**
	* @brief angle turned about center in plane of wheels
	*/
	float turnangle;
	/**
	 * @brief normal vector to bike
	 */
	vector3f normal;

	/**
	 * @brief keyboard operations
	 */
  float l;
  float pause;
	float a;
	float d;
	float w;
	float s;
	float n;
	float sp;
	float vn;
	float tn;
	float distance;

	/**
	 * @brief to generate positions of obstacles
	 */
  float * p;
	float * rp;
	float * gp;
	/**
	 *@brief  score scored by player
   */
  int score;

  /**
   *@brief horizontal and vertical components of normal vector of plane
   */
	float hor;
	/**
	 *@brief horizontal and vertical components of normal vector of plane
	 */
	float ver;
	/**
	 * @brief obstacle handling
	 */
	void rockcollisions();
	/**
	 *@brief  scoring by passing
	 */
	void  collision();





};
/**
 * @brief  loading terrains and models into object physics
 * @param p terrain
 * @param model model
 * @return object total with physics unified
 */
  Object* load(terrain* p,GLMmodel* model);
  /**
   * @brief terrain position calculator
   * @param terra terrain
   * @return positions array pointer
   */
 float* fun(terrain* terra);
