#ifndef POINT3F_H_
#define POINT3F_H_

#include <GL/gl.h>

class Point3f
{
public :
	GLfloat x,y,z;
	Point3f(){
		x=y=z=0;
	}
	Point3f(GLfloat x1,GLfloat y1,GLfloat z1){
			x=x1;
			y=y1;
			z=z1;
		}
	void set_Cords(GLfloat x1,GLfloat y1,GLfloat z1)
	{
		x=x1;
		y=y1;
		z=z1;
	}
	GLfloat get_x() const {return x;}
	GLfloat get_y() const {return y;}
	GLfloat get_z() const {return z;}

	Point3f operator -(const Point3f& a){
			Point3f result;
			result.x=this->x-a.x;
			result.y=this->y-a.y;
			result.z=this->z-a.z;
			return result;
		}

};
//Sphere sai(-3.0,3.0,0.0,3.0);
//		Point3f p(5.0,0.0,0.0);
//		Vector3f dir(5.0,4.5,0.0);
//		Point3f ans(0.0,0.0,0.0);
//		bool b=sai.sphere_intersection(p,dir,ans);
#endif /* SAI_H_ */
