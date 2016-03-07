/*
 * Vector3f.cpp

 *
 *  Created on: 12-Sep-2014
 *      Author: vignan_pc
 */
#pragma once
#include "math.h"
//using namespace std;




class Vector3f{
	public:
	float x,y,z;
	Vector3f(){x=0;y=0;z=0;}

	~Vector3f(){}
	Vector3f(float x1,float y1,float z1){
		x=(x1);y=(y1);z=z1;}
	Vector3f(const Vector3f& a){
					this->x=a.x;
					this->y=a.y;

					this->z=a.z;
			}


//	Vector3f operator -(){
//		Vector3f result;
//		result.x=-x;
//		result.y=-y;
//		result.z=-z;
//		return result;
//	}

	Vector3f operator +(const Vector3f& a){

		return Vector3f(this->x+a.x,
		this->y+a.y,
		this->z+a.z);

	}

	float operator *(const Vector3f& a){
			float result=
			this->x*a.x+
			this->y*a.y+
			this->z*a.z;
			return result;
		}

	Vector3f operator *( float c){
			Vector3f a;
			a.x=c*this->x;
			a.y=c*this->y;
			a.z=c*this->z;
			return a;
		}

	Vector3f operator -(const Vector3f& a){
		Vector3f result;
		result.x=this->x-a.x;
		result.y=this->y-a.y;
		result.z=this->z-a.z;
		return result;
	}

	void 	operator *=	(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}
	Vector3f cross(const Vector3f &b){
		Vector3f c;

		c.x=this->y*b.z-b.y*this->z;
		c.y=b.x*this->z-this->x*b.z;
		c.z=this->x*b.y-b.x*this->y;
		return c;
	}

	float magnitude(){
		return sqrt((this->x)*(this->x)+(this->y)*(this->y)+(this->z)*(this->z));
	}
	Vector3f unitvec(){
		Vector3f c;
		float f=this->magnitude();
		c.x=this->x/f;
		c.y=this->y/f;
		c.z=this->z/f;
		return c;
	}
	Vector3f smulp(float c){
		Vector3f a;
		a.x=c*this->x;
		a.y=c*this->y;
		a.z=c*this->z;
		return a;
	}
	void Normalize(){

		float c=1/(magnitude());
		this->x=this->x*c;
		this->y=this->y*c;
		this->z=this->z*c;


	}
//	Vector3f convert(Point3f &a){
//		Vector3f r;
//		r.x=a.x;
//		r.y=a.y;
//		r.z=a.z;
//		return r;
//	}
//	Vector3f convert(Point3f a){
//			Vector3f r;
//			r.x=a.x;
//			r.y=a.y;
//			r.z=a.z;
//			return r;
//		}

};






