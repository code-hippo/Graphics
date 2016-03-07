
#include <iostream>
#include <GL/gl.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include "read.h"


using namespace std;

UVN::UVN(){
	Ref =vector1(3,0);
	Eye =vector1(3,0);
	U =vector1(3,0);
	// UP =vector1(3,0);
	V =vector1(3,0);
	N = vector1(3,0);
	near =0;
	far =0;
	wl=0;wr=0;wb=0;wt=0;
	wlt= vector1(3,0);wrt= vector1(3,0);wlb= vector1(3,0);wrb= vector1(3,0);
	//fileread1();
};

UVN::~UVN(){};

void UVN::fileread1(){
	ifstream myReadFile;
	myReadFile.open("input.txt");
	vector1 Up=vector1(3,0);
	if (myReadFile.is_open())
	{
	 	int i=0;
		while(!(myReadFile.eof())) // To get you all the lines.
	  {
	 		string str1;
			getline(myReadFile,str1);// Saves the line in string.
		 	vector<float>  out1(4,0);
		 	split(str1,out1);
		 	if(i==0){
				for(int i0=0;i0<3;i0++)
				{
	       	Ref[i0]=((out1[i0]));
			 	}
		 	}
	 	 	else if(i==1){
			 	for(int i0=0;i0<3;i0++)
				{
					N[i0]=(out1[i0]);
			 	}
				N=vunit(N);
			}
			else if(i==2){
				for(int i0=0;i0<3;i0++)
				{
					  Up[i0]=(out1[i0]);
				}
			Up=vsub(vunit(Up),vscalarmult(N,vdot(vunit(Up),N)));
			V=vunit(Up);
			U=vunit(vcross(V,N));
			}
			else if(i==3){
		 		Eye[0]=0;
		 		Eye[1]=0;
		 		Eye[2]=(-out1[0]);

			}
			else if(i==4){
				near=out1[0];
			}
			else if(i==5){
				far=out1[0];
			}
			else if(i==6){
				for(int i0=0;i0<4;i0++)
				{
					if(i0==0){
						wl=out1[0];
				  }
				  else if(i0==1){
					  wr=out1[1];
				  }
				  else if(i0==2){
					  wb=out1[2];
				  }
				  else if(i0==3){
					  wt=out1[3];
				  }
			 	}
			}
			// Prints our STRING.
			i++;
		}
	}
	myReadFile.close();
	wlt[0]=(-wl);wlt[1]=(wt);wlt[2]=(near+Eye[2]);
	wrt[0]=(wr);wrt[1]=(wt);wrt[2]=(near+Eye[2]);
	wlb[0]=(-wl);wlb[1]=(-wb);wlb[2]=(near+Eye[2]);
	wrb[0]=(wr);wrb[1]=(-wb);wrb[2]=(near+Eye[2]);
}

typedef vector<float> vector1;
float magnitude(vector1 a){
		return sqrt((float)(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]));
	}

vector1 vsum(vector1 a,vector1 b){
	vector1 c;
	c.push_back(a[0]+b[0]);
	c.push_back(a[1]+b[1]);
	c.push_back(a[2]+b[2]);
	return c;
}

vector1 vsub(vector1 a,vector1 b){
	vector1 c;
	c.push_back(a[0]-b[0]);
	c.push_back(a[1]-b[1]);
	c.push_back(a[2]-b[2]);
	return c;
}

vector1 vscalarmult(vector1 a,float	 c){
	a[0]=c*a[0];
	a[1]=c*a[1];
	a[2]=(c*a[2]);
	return a;
}

float vdot(vector1 a,vector1 b){
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

vector1 vcross(vector1 a, vector1 b){
	vector1 c;
	c.push_back(a[1]*b[2]-b[1]*a[2]);
	c.push_back(b[0]*a[2]-a[0]*b[2]);
	c.push_back(a[0]*b[1]-b[0]*a[1]);
	return c;
}

vector1 vunit(vector1 a){
	vector1 c;
	float f=magnitude(a);
	c.push_back(a[0]/f);
	c.push_back(a[1]/f);
	c.push_back(a[2]/f);
	return c;
}

vector1 vsetval(float x,float y,float z){
	vector1 v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	return v;
}

void split(string str,vector<float>& ans)
{
	string s=str;
	istringstream iss(s);
	float sub;
	int i=0;
	while(iss >> sub && i < (int)ans.size()){
		ans[i]=sub;
		i++;
	}

}

UVN* load(){
	UVN * p;
	p=new UVN();
	return p;
}
