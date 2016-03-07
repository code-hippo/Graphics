/*
 * g1.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: bhargavvar
 */


//reading text

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <GL/gl.h>
using namespace std;
vector<GLfloat> out(string str)
{
  string s(str);
  istringstream iss(s);
  vector<GLfloat> ans;
  while(iss){
    GLfloat sub;
    iss >> sub;
    ans.push_back(sub);
  }

  return ans;
}
