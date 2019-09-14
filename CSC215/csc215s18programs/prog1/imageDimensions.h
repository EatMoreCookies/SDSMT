/*************************************************************************//**
* @file
* @brief header file used by imageDimensions.cpp
****************************************************************************/
#ifndef _IMAGEDIMESIONS_H_
#define _IMAGEDIMENSIONS_H_
#define _CRT_SECURE_NO_WARNGINGS
#include<fstream>
using namespace std;

void GIFdimensions( ifstream &fin, unsigned int &heightInt, 
	unsigned int &widthInt );

void BMPdimensions( ifstream &fin, unsigned int &heightInt, 
	unsigned int &widthInt );

void PNGdimensions( ifstream &fin, unsigned int &heightInt, 
	unsigned int &widthInt );

#endif
