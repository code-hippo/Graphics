/*
 * highscores.h
 *
 *  Created on: 09-Sep-2013
 *      Author: vignan_pc
 */
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

/**
 * @brief to store and load game highscores during runtime
 */
typedef struct{
		int score;
		char * name;
}my_struct;

/**
 * @brief highscores update
 * @param name name of highscorer
 * @param score highscore scored
 */


void scoreupdate(char* name,int score);
