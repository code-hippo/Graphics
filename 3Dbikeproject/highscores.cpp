/*
 * highscores.cpp
 *
 *  Created on: 09-Sep-2013
 *      Author: vignan_pc
 */


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

#include "highscores.h"





string line;
//create temporary struct so you'll be able to fill the vector
my_struct * temp=new my_struct[10];



void scoreupdate(char * name,int score)
{
		fstream myfile ;
		char* p="High_scores.txt";
		myfile.open(p);
		string line;
		cout<<"the file "<<p<< " is opened"<<endl;
		for(int i=0;i<10;i++)
		{

		    myfile>>line;
		    char * p1;
		    p1=const_cast<char*>(line.c_str());

		    temp[i].name=p1;
		    myfile>>line;
		    p1=const_cast<char*>(line.c_str());
		    temp[i].score=atoi(p1);
		}

		myfile.clear();

		for(int i=0;i<10;i++)
		{
				char * q =temp[i].name;
				int k    =temp[i].score;
				if(score>=k){
				temp[i].name=name;
				temp[i].score=score;
				name=q;
				score=k;
				}
		}


		if(myfile.fail())
		{
				cout<<"what happened"<<endl;
		}
		else if(myfile.good())
		{
				if(myfile.is_open())
				{

	        	for(int i=0;i<10;i++)
	        	{
	        	myfile<<temp[i].name<<" "<<temp[i].score<< "\n";
	        	}

	      }
	  }

		myfile.close();
		cout<<"the file "<<p <<" is closed"<<endl;
}
