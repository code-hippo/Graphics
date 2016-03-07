/*
 * scores.h
 *
 *  Created on: 08-Sep-2013
 *      Author: vignan_pc
 */

#ifndef SCORES_H_
#define SCORES_H_

/**
 * @brief different traks used
 */
class Track{
private:

public:
	int Track_name;
	char* Names[5];
	int scores[5];
	void ChangehighScore(int Track_name,char* playername,int Score);
};


#endif /* SCORES_H_ */
