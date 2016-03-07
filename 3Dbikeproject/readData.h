/*
 * readData.h
 *
 *  Created on: 12-Aug-2013
 *      Author: vignan_pc
 */

#ifndef READDATA_H_
#define READDATA_H_
/**
 * @brief to read pixels to get heightmap
 */

class Image {
	public:
		Image(char* ps, int w, int h);
		~Image();
		char* pixels;
		int width;
		int height;
};

/**
 * @brief loads image pixelmaps
 * @param filename of the image used
 * @return pixelmap
 */
Image* loadImage(const char* filename);



#endif /* READDATA_H_ */
