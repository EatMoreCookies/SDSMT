/*************************************************************************//**
* @file
* @brief Contains the functions that find the height and width dimensions of
*        file images. 
****************************************************************************/
#include"imageDimensions.h"

/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function goes through the GIF image looking for the image's dimensions.   
* The image's width is found in bytes 7 and 8 and its height in bytes 9 and 
* 10. Because the file was opened in binary, all the dimensions are in charac-
* ter form. Therefore, this function creates the integer's dimensions by using 
* bitwise operators to combines the characters. 
*
* @param[in,out]     fin - file input stream
* @param[out]     heightInt - stores the height of the image as an integer
* @param[out]     widthInt - stores the width of the image as an integer
*
****************************************************************************/
void GIFdimensions( ifstream &fin, unsigned int &heightInt, 
    unsigned int &widthInt )
{
    unsigned char width[20] = "";
    unsigned char height[20] = "";
    
    widthInt = 0;
    heightInt = 0;
    
    
    //seek to width bytes
    fin.seekg( 7, ios::beg );
    
    fin.read( ( char * ) &width[0], 1 );
    
    fin.seekg( -2, ios::cur );
    
    fin.read( ( char * ) &width[1], 1 );

    
    
    //create width integer
    widthInt = widthInt | width[0];

    widthInt = widthInt << 8;

    widthInt = widthInt | width[1];

    
    
    //find height
    fin.seekg( 9, ios::beg );

    fin.read((char *) &height[0], 1 );

    fin.seekg( -2, ios::cur );

    fin.read( ( char * ) &height[1], 1 );
    
    
    
    //create height integer
    heightInt = heightInt | height[0];

    heightInt = heightInt << 8;

    heightInt = heightInt | height[1];
}
/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function goes through the BMP looking for the image's dimensions. The
* image's width is found in bytes 19 through 22 and its height in bytes 23 
* through 26. Because the file was opened in binary, all the dimenions are in 
* character form. Therefore, this function creates the integer's dimensions by 
* using bitwise operators to combines the characters.
* 
* @param[in,out]     fin - file input stream
* @param[out]     heightInt - stores the height of the image as an integer
* @param[out]     widthInt - stores the width of the image as an integer
*
****************************************************************************/
void BMPdimensions( ifstream &fin, unsigned int &heightInt, 
    unsigned int &widthInt )
{
    unsigned char width[20] = "";
    unsigned char height[20] = "";
    int i;
    
    widthInt = 0;
    heightInt = 0;

    
    
    //seek to first width byte
    fin.seekg( 21, ios::beg );

    //find width bytes (higher bytes are in higher order in the integer)
    for ( i = 0; i < 4; ++i )
    {
        fin.read( ( char * ) &width[i], 1 );

        fin.seekg( -2, ios::cur );
    }
    
    
    
    //form width integer
    widthInt = widthInt | width[0];
    
    for ( i = 1; i < 4; ++i )
    {
        widthInt = widthInt << 8;

        widthInt = widthInt | width[i];
    }
    
    
    
    //seek to first height byte (this is the heighest order byte)
    fin.seekg( 25, ios::beg );

    //find height bytes 
    for ( i = 0; i < 4; ++i )
    {
        fin.read( ( char * ) &height[i], 1 );

        fin.seekg( -2, ios::cur );
    }

    
    
    //form height integer.
    heightInt = heightInt | height[0];

    for ( i = 1; i < 4; ++i )
    {
        heightInt = heightInt << 8;
        
        heightInt = heightInt | height[i];
    }
}
/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function goes through the PNG looking for the image's dimensions. The
* image's width is found in bytes 17 through 20 and its height in bytes 21
* through 24. Because the file was opened in binary, all the dimenions are in
* character form. Therefore, this function creates the integer dimensions by
* using bitwise operators to combines the characters.
*
* @param[in,out]     fin - file input stream
* @param[out]     heightInt - stores the height of the image as an integer
* @param[out]     widthInt - stores the width of the image as an integer
*
****************************************************************************/
void PNGdimensions( ifstream &fin, unsigned int &heightInt, 
    unsigned int &widthInt )
{
    unsigned char width[20] = "";
    unsigned char height[20] = "";
    int i;
    
    widthInt = 0;
    heightInt = 0;
    
    
    
    //seek to first width byte (this is heighest order byte)
    fin.seekg( 16, ios::beg );

    for ( i = 0; i < 4; ++i )
    {
        fin.read( ( char * ) &width[i], 1 );
    }
    
    
    
    //form width integer.
    widthInt = widthInt | width[0];
    
    for ( i = 1; i < 4; ++i )
    {
        widthInt = widthInt << 8;

        widthInt = widthInt | width[i];
    }
    
    
    
    //seek to first height byte (this is heighest order byte)
    fin.seekg( 20, ios::beg );

    //read in height bytes
    for ( i = 0; i < 4; ++i )
    {
        fin.read( ( char * ) &height[i], 1 );
    }

    
    
    //form height integer.
    heightInt = heightInt | height[0];

    for ( i = 1; i < 4; ++i )
    {
        heightInt = heightInt << 8;
        
        heightInt = heightInt | height[i];
    }
}