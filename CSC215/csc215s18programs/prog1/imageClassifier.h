/*************************************************************************//**
* @file
* @brief header file used by imageClassifier.cpp
****************************************************************************/
#ifndef _IMAGECLASSIFIER_H_
#define _IMAGECLASSIFIER_H_
#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include<cctype>
#include<cstring>
using namespace std;

bool isBMP( ifstream &fin );

bool isGIF( ifstream &fin );

bool isJPG( ifstream &fin );

bool isPNG( ifstream &fin );


#endif