/*
 * physics.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: bhargavvar
 */


#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "physics.h"
#include "terrain.h"
#include "glm.h"
#include "Obst.h"
#include <GL/glut.h>

using namespace std;

const float PI = 3.1415926535f;
const float fps =100;
const float updt=1/fps;

Object::~Object(){
	delete _terrain;
	delete _model;
}

float* fun(terrain* terra)
{
	float * p;
	p=new float[20];
	for (int i=0;i<10;i++)
	{
		p[2*i]=RandomFloat(0,terra->width()-6);
		p[2*i+1]=RandomFloat(0,terra->length()-6);
	}
	return p;
}

Object::Object(terrain* q,GLMmodel* model)
{
    a=0;
    d=0;
    w=0;
    s=0;
    sp=0;
    n=0;
    l=0;
    p=0;
    onterrainborder=false;
    pos.x=128;
    pos.y=0;

    hor=0;
    ver=0;
    pos.z=128;

    _terrain=q;
    _model=model;
    velocity=setvalues(.0,0,0);
	  accelerate=setvalues(0.00,0,0);
    bikeangle=00;

    size0=.035;
    normal=setvalues(cos(((bikeangle+90)/180)*PI),0,-cos(((bikeangle)/180)*PI));

    onterrainborder=false;
    timeaccumulator=1.0f;
    terrainlfactor=1;
    distance=0;
    vn=0;
    tn=0;

    rp=fun(q);
    p=fun(q);
    gp=fun(q);

    turnangle=0;
    score=0;
}


void Object::rockcollisions()
{
	for(int i=0;i<10;i++)
	{
		if((gp[2*i]-1.45<pos.x &&pos.x<gp[2*i]+1.45) && gp[2*i+1]-4.5<pos.z &&pos.z<gp[2*i+1]+1.45 )
		{
			score-=20;
			if((max(gp[2*i]-1.45-pos.x,pos.x-gp[2*i]-1.45))>(max(gp[2*i+1]-1.45-pos.z,pos.z-gp[2*i+1]-1.45)))
			{
				velocity.x=0;
				if(velocity.z>0){
					bikeangle=180;
				}
				else bikeangle=0;
				if(gp[2*i]-1.45-pos.x>pos.x-gp[2*i]-1.45){
					pos.x=gp[2*i]-2;
				}
				else pos.x=gp[2*i]+2;
			}
			else
			{
				velocity.z=0;
				if(velocity.x>0){
					bikeangle=270;
				}
				else bikeangle=90;
				if(gp[2*i+1]-1.45-pos.z>pos.z-gp[2*i+1]-1.45)
				{
					pos.z=gp[2*i+1]-2;
				}
				else pos.z=gp[2*i+1]+2;
			}
			break;
		}
	}
}

void Object::collision()
{
	for(int i=0;i<10;i++)
	{
		if((rp[2*i]-1.15<pos.x &&pos.x<rp[2*i]+1.15) && rp[2*i+1]-1.15<pos.z &&pos.z<rp[2*i+1]+1.15 )
		{
	    score+=15;
			rp[2*i]=RandomFloat(0,_terrain->width()-6);
			rp[2*i+1]=RandomFloat(0,_terrain->length()-6);
		}
	}


for(int i=0;i<10;i++)
{
	if((p[2*i]-1.15<pos.x &&pos.x<p[2*i]+1.15) && p[2*i+1]-1.15<pos.z &&pos.z<p[2*i+1]+1.15 )
	{
    score+=10;
		p[2*i]=RandomFloat(0,_terrain->width()-6);
		p[2*i+1]=RandomFloat(0,_terrain->length()-6);
	}
}
}

void Object::setVelocityX(float dt)
{
	velocity.x=dt;
}

void Object::setVelocityY(float dt)
{
	velocity.y=dt;
}

void Object::setVelocityZ(float dt)
{
	velocity.z=dt;
}

void Object::posupdate(float dt)
{
	float  maxX= ((int)_terrain->w-1)*terrainlfactor-18*size0;
	float  maxZ= ((int)_terrain->l-1)*terrainlfactor-18*size0;
  float  minX= 18*size0;
  float  minZ=18* size0;

  if ( pos.x<size0 || pos.z<size0 || pos.x>maxX-size0 || pos.z>maxZ-size0)
  {
  	onterrainborder= true;
  }
  pos.x += velocity.x* dt;
  pos.z += velocity.z* dt;
  distance=distance+sqrt((velocity.x)*velocity.x*dt*dt+velocity.z*velocity.z*dt*dt);

  if(pos.x<18*size0){
   	setVelocityX(0);
  	bikeangle=-90;
    pos.x=20*size0;
		if(velocity.x>0 ){
    	bikeangle=180+180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
    	}
    	else{
    		bikeangle=180-180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
    	}
  }
  if(pos.z<18*size0)
  {
  	pos.z-=velocity.z*dt;
  	setVelocityZ(0);
    bikeangle=180;
    pos.z=20*size0;
    if(velocity.x>0 ){
    bikeangle=180+180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
    }
    else{
    	bikeangle=180-180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
    }
  }
  if(pos.x>maxX)
	{
  	setVelocityX(0);
  	bikeangle=+90;
    pos.x=maxX-10*size0;
    if(velocity.x>0 ){
  	  bikeangle=180+180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
    }
    else{
    	bikeangle=180-180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
    }
  }
  if(pos.z>maxZ)
  {
  	setVelocityZ(0);
    bikeangle=00;
    pos.z=maxZ-10*size0;
    if(velocity.x>0 ){
    	bikeangle=180+180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
    }
		else{
			bikeangle=180-180*(1/PI)*acos(velocity.z/magnitude(setvalues(velocity.x,0,velocity.z)));
		}
  }

  vector3f a=accelerate;

	if(pos.y<-.01)
	{
		if(velocity.y<0)
		{
			velocity.y=0;
		}
	}

	if(pos.y>0)
	{
		velocity.y-=0.000006*dt;
	}
	else
	{
	}
	pos.y+=velocity.y*dt;

}

void Object::bikeangleupdate(float dt)
{
	if(pos.y<.8){
	if (d==1)
	{
     float hspeed=magnitude(setvalues(velocity.x,0,velocity.z));
     velocity.x=hspeed*((1.3-dt/1000)/1.3)*cos((-dt*90/1000+90+bikeangle)*PI/180);
     velocity.z=-hspeed*((1.3-dt/1000)/1.3)*cos((-dt*90/1000+bikeangle)*PI/180);
     bikeangle-=dt*90/1000;
     normal=setvalues(cos(((bikeangle+90)/180)*PI),0,-cos(((bikeangle)/180)*PI));
	}
	if(a==1)
	{
     float hspeed=magnitude(setvalues(velocity.x,0,velocity.z));
     velocity.x=hspeed*((1.3-dt/1000)/1.3)*cos((+dt*90/1000+90+bikeangle)*PI/180);
     velocity.z=-hspeed*((1.3-dt/1000)/1.3)*cos((+dt*90/1000+bikeangle)*PI/180);
     bikeangle+=dt*90/1000;
     normal=setvalues(cos(((bikeangle+90)/180)*PI),0,-cos(((bikeangle)/180)*PI));
	}
	}
}

void Object::velupdate(float dt)
{
  if(pos.y<.8){
	 turnangle=(1/PI)*180*(dotproduct(setvalues(cos((90+bikeangle)*PI/180),0,-cos((bikeangle)*PI/180)),
												 NormalAt(_terrain,pos.x,pos.z)))
  											/(magnitude(NormalAt(_terrain,pos.x,pos.z)));
  }
  hor=cos(turnangle*PI/180);
  ver=sin(turnangle*PI/180);
	if(pos.y<.8){
		vn+=0.000008*dt;
			if(vn>0.08){
				vn=0.08;
			}
	    if(n==1)
			{
				if(magnitude(velocity)>=0)
				{
					if(vn>0){
						vn-=0.00004*dt;
						if(dotproduct(velocity,setvalues(cos((bikeangle+90)*PI/180),0,(-1)*cos((bikeangle)*PI/180)))+.01>=0)
						{
							velocity.y+=0.00004*ver*dt;
							velocity.z-=0.000012*hor*dt*(cos(bikeangle*PI/180));
							velocity.x+=0.000012*dt*hor*(cos((bikeangle+90)*PI/180));

			    	}
					}
				}
			}

			if(w==1)
			{
				if(magnitude(velocity)>=0)
				{
					if(dotproduct(velocity,setvalues(cos((bikeangle+90)*PI/180),0,(-1)*cos((bikeangle)*PI/180)))+.01>=0)
					{
						velocity.y+=0.00002*ver*dt;
						velocity.z-=0.000006*hor*dt*(cos(bikeangle*PI/180));
					  velocity.x+=0.000006*dt*hor*(cos((bikeangle+90)*PI/180));

				  }
				}
			}
			if(s==1)
			{
				if(magnitude(velocity)>=0)
				{
		      if(dotproduct(velocity,setvalues(cos((bikeangle+90)*PI/180),0,(-1)*cos((bikeangle)*PI/180)))>0)
			    {
		       	velocity.y+=0.000027*ver*dt;
					 	velocity.z+=0.0000085*dt*hor*(cos(bikeangle*PI/180));
					 	velocity.x-=0.0000085*dt*hor*(cos((bikeangle+90)*PI/180));
					}
		      else
					{
						velocity.y-=0.000003*ver*dt;
		        velocity.z+=0.0000009*dt*hor*(cos(bikeangle*PI/180));
		        velocity.x-=0.0000009*dt*hor*(cos((bikeangle+90)*PI/180));
		      }
				}
			}
			if(sp==1)
			{
				if(magnitude(velocity)>=0)
				{
					if(dotproduct(velocity,setvalues(cos((bikeangle+90)*PI/180),0,(-1)*cos((bikeangle)*PI/180)))>0)
					{
					 	velocity.y-=0.0000035*dt*ver;
					 	velocity.z+=0.000001*dt*hor*(cos(bikeangle*PI/180));
					 	velocity.x-=0.000001*dt*hor*(cos((bikeangle+90)*PI/180));
					}
				}
			}

			if(dotproduct(velocity,setvalues(cos((bikeangle+90)*PI/180),0,(-1)*cos(bikeangle)*PI/180))>0)
			{
       	velocity.x-=0.0000002*dt*hor*(cos((bikeangle+90)*PI/180));
        velocity.z+=0.0000002*dt*hor*(cos(bikeangle*PI/180));
	    }
   }
}

void Object::draw()
{
	if (_model == NULL) {
		return;
	}

	float scale = 50.0f / max(_terrain->width() - 1, _terrain->length() - 1);
	glPushMatrix();
	glTranslatef(pos.x,heightAt(_terrain,pos.x,pos.z)+18*size0+pos.y, pos.z);

	glColor3f(1, 1, 1);
  glRotatef(+bikeangle,0,1,0);
  if(pos.y<0.8)
  {
   	if(a==1){
    	glRotatef(17,normal.x,1,normal.z+10);
    }
    if(d==1){
      glRotatef(-17,normal.x,01,normal.z+10);
		}
  }

	glRotatef(turnangle,normal.z+10,0,-normal.x);
	glRotatef(-15,normal.z+10,0,-normal.x);
	collision();
	rockcollisions();

	glmDraw(_model,GLM_COLOR);

	glPopMatrix();
}

vector3f Object::glulookat()
{
	float scale = 50.0f / max(_terrain->width() - 1, _terrain->length() - 1);
	vector3f bikelookat;
	bikelookat.z=0.4*(-1)*cos(bikeangle*PI/180);
	bikelookat.y=0.3;
	bikelookat.x=0.4*(1)*cos((bikeangle+90)*PI/180);
	return bikelookat;
	}

vector3f Object::posonterrain()
{
	vector3f bikeposterra;
	float     scale = 50.0f / max(_terrain->width() - 1, _terrain->length() - 1);

	bikeposterra.x=scale*(pos.x-(float)(_terrain->width() - 1) / 2);
	bikeposterra.y=scale*(18*size0+pos.y+heightAt(_terrain,pos.x,pos.z));
	bikeposterra.z=scale*(pos.z-(float)(_terrain->length() - 1) / 2);
 	return bikeposterra;
}

Object* load(terrain* terra,GLMmodel* mod)
{
  Object* q;
  q=new Object(terra,mod);
  return q;
}

void Object::framestime(float updt)
{
	while(updt>0)
	{
	  if (timeaccumulator > 1.0f)
	  {
			timeaccumulator =1.0f;
	  }
	  if(timeaccumulator < updt)
	  {
     	bikeangleupdate(timeaccumulator);
		  velupdate(timeaccumulator);
		  posupdate(timeaccumulator);
		  updt-=timeaccumulator;
	  }
	  else
	  {
			bikeangleupdate(updt);
			velupdate(updt);
			posupdate(updt);
      updt=0;
	  }
	}
  if(bikeangle <0 )
		  bikeangle=bikeangle+360;
	if(bikeangle >360)
		  bikeangle=bikeangle-360;
}
