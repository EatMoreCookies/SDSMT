/*************************************************************************//**
* @file
* @brief Contains the functions that classify images as GIF, BMP, PNG, or 
*        JPG.
****************************************************************************/
#include"imageClassifier.h"

/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function checks to see if the image given is a GIF image. It does this
* by seeing if the first 6 bytes of the image is GIF89a or GIF87a. 
*
* @param[in,out]   fin - file input stream
* 
* returns true - is a GIF image
* returns false - is not a GIF image
****************************************************************************/
bool isGIF( ifstream &fin )
{
    char GIFdefiner[20] = "";
    
    
    
    //seek to the beginning
    fin.seekg( 0, ios::beg );
    
    //read in first two bytes
    fin.read( ( char * ) &GIFdefiner, 6 );
    
    
    
    //see if the first two bytes match the criteria of a GIF image
    if ( ( strcmp(GIFdefiner, "GIF89a" ) == 0 ) 
        || ( strcmp ( GIFdefiner, "GIF87a" ) == 0) )
    {
        return true; 
    }
    
    
    
    else
    {
        return false;
    }
}

/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function checks to see if the image given is a BMP image. It does this
* by seeing if the first 2 bytes of the image are the characters BM
*
* @param[in,out]   fin - file input stream
*
* returns true - is a BMP image
* returns false - is not a BMP image
****************************************************************************/
bool isBMP( ifstream &fin )
{
    char BMPdefiner[20] = "";

    
    
    //seek to the begining of the file 
    fin.seekg( 0, ios::beg );
    
    //read in first two bytes
    fin.read( ( char * ) &BMPdefiner, 2 );

    
    
    //see if the first two bytes == BM
    if ( strcmp( BMPdefiner, "BM" ) == 0 )
    {
        return true;
    }

    
    
    else
    {
        return false; 
    }
}

/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function checks to see if the image given is a PNG image. It does this
* by seeing if the first 8 bytes have the values of 137, 80, 78, 71
* 13, 10, 26, 10, respectively. 
*
* @param[in,out]   fin - file input stream
*
* returns true - is a PNG image
* returns false - is not a PNG image
****************************************************************************/
bool isPNG( ifstream &fin )
{
    bool equal = false;
    unsigned char PNGdefiner[20] = "";
    
    //stores what the first 8 bytes of a PNG image are
    int PNGtesting[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
    
    int i;
    
    
    
    //seek to the begining of the file
    fin.seekg( 0, ios::beg );

    //read in the first 8 bytes 
    fin.read( ( char * ) &PNGdefiner, 8 );

    
    
    //see if every byte is equivalent to the necessary criteria of a PNG
    for ( i = 0; i < 8; ++i )
    {
        
        if ( PNGtesting[i] == PNGdefiner[i] )
        {
            equal = true;
        }

        
        
        else
        {
            return false;
        }

    }

    return equal;
}

/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function checks to see if the image given is a JPG image. It does this
* by seeing if the first 2 bytes have the values of 255 and 216 respectively,
* and the last 2 bytes have the values of 255 and 217 respectively.  
* 
* @param[in,out]   fin - file input stream
*
* returns true - is a JPG image
* returns false - is not a JPG image
****************************************************************************/
bool isJPG( ifstream &fin )
{
    bool equal = false;
    unsigned char JPGdefiner[20] = "";
    
    //stores the four bytes that a JPG image will have
    int JPGtesting[4] = { 255, 216, 255, 217 };
    
    int i = 0;

    
    
    //seek to the beginning
    fin.seekg( 0, ios::beg );

    fin.read( ( char * ) &JPGdefiner, 2 );

    //seek to the end
    fin.seekg( -2, ios::end );

    fin.read( ( char * ) &JPGdefiner[i + 2], 2 );

    
    
    //making sure all read in values match with the certain criteria
    for ( i = 0; i < 4; ++i )
    {
        if ( JPGdefiner[i] == JPGtesting[i] )
        {
            equal = true;
        }

        
        
        else
        {
            return false;
        }
        
        
    }
    
    return equal;
}