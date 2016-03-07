/*
 * screenscore.h
 *
 *  Created on: 08-Sep-2013
 *      Author: vignan_pc
 */

#ifndef SCREENSCORE_H_
#define SCREENSCORE_H_
/**
 * @brief to sive step integers of decimals
 * @param num the number in decimal
 * @return return the integer closest
 */
float decimalval(float num);
/**
 * @brief to draw time on sceen
 * @param Time time input to be drawn
 */
void drawTime(float Time);
/**
 * @brief to draw velocity on screen
 * @param Time velocity of the object
 */
void drawVelocity(float Time);
/**
 * @brief to draw distance travelled by d body
 * @param Time distance travelled
 */
void drawDist(float Time);
/**
 * @brief to draw all above functions in single step
 */
void drawover();
/**
 * @brief to draw score
 * @param score points scoed by player
 */
void drawscore(int score);
#endif /* SCREENSCORE_H_ */
