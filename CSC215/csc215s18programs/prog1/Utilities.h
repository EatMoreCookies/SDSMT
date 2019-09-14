/*************************************************************************//**
* @file
* @brief header file used by Utilities.cpp
****************************************************************************/
#ifndef _UTILITIES_H
#define _UTILITIES_H
#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<cctype>
#include<algorithm>
#include<cstring>
#include<fstream>
#include<direct.h>
#include<io.h>
#include"imageClassifier.h"
#include"imageDimensions.h"
using namespace std;



bool checkArgc( int argNum );

bool changeDir( char filePath[] );

char *getCurrDir();

void dirListing( ifstream &fin );

void restoreGIFImage( ifstream &fin, char fileName[] );

void restoreBMPImage( ifstream &fin, char fileName[] );

void restorePNGImage( ifstream &fin, char fileName[] );

void restoreJPGImage( ifstream &fin, char fileName[] );

char *intToString( unsigned int height, unsigned int width,
	char widthHeight[] );

void identifyImage( ifstream &fin, char fileName[] );

#endif 

