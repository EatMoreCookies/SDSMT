/*************************************************************************//**
* @file
* @brief Contains all the program functions that are not main, that do not
*        classify images, or that do not find the dimensions of images. 
****************************************************************************/
#include"Utilities.h"

/*************************************************************************//**
* @author Nathaniel Fagrey. 
*
* @par Description:
* This function checks to make sure that the number of arguments entered
* in the command line is at least two: one for the program.exe and one for a
* directory. 
*
* @param[in]      argNum - number of arguments on the command line
*
* @returns  true - correct number of arguments entered
* @returns  false - wrong number of arguments entered. 
*
****************************************************************************/
bool checkArgc( int argNum )
{
    if ( argNum < 2 )
    {
        cout << "In order to use this program, you must enter the "
            << "directories (via command line) that contain the " 
            << endl << "image files " << "you would like to restore. "
            << endl;
            

        return false;
    }
    
    
    
    else
    {
        return true; 
    }
}
/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function changes the directory that the program starts in to one of 
* the directories entered by the user. 
*
* @param[in]      filepath[] - a string that holds the directory that we are
*                              trying to change to. 
* @returns  true - successfully changed directories
* @returns  false - failed to change directories. 
*
****************************************************************************/

bool changeDir( char filePath[] )
{
    if ( strcmp( filePath, ".." ) == 0 || strcmp( filePath, "." ) == 0 )
    {
        cout << "Not allowed to process directories that are: "
            << filePath <<  " " << endl;

        return false;
    }

    
    
    if ( _chdir( filePath ) == 0 )
    {
        cout << "Changed directories successfully to: " << filePath << endl;
        
        return true;
    }

    
    
    else
    {
        cout << "Failed to process directory: " 
            << filePath << endl;

        return false;
    }
}
/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function outputs the current directory that we are in. It then passes 
* back a pointer to that directory. 
*
* @returns currDir - currDir - current directory
*
****************************************************************************/
char *getCurrDir()
{
    char *currDir;

    currDir = _getcwd( NULL, _MAX_PATH + 1 );

    return currDir;
}
/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function goes through the given directory looking for files. Once a 
* file is found, the function opens it and calls a classifier function to see 
* if it is an image file.
*    
* @param[in,out]  fin - file input stream
*
****************************************************************************/
void dirListing( ifstream &fin )
{
    _finddata_t aFile;
    intptr_t dHandle;
    char pattern[30] = "*.*";
    char fileName[_MAX_PATH + 1] = "";
    
    dHandle = _findfirst( pattern, &aFile );
    
    if ( dHandle == -1 )
    {
        return;
    }
    
    
    
    //runs through all files/sub-directories
    do
    {
        //makes sure that it is a file and that it is not named "." or ".."
        if ( !( aFile.attrib & _A_SUBDIR ) && ( aFile.name != "." ) && 
            ( aFile.name != ".." ) )
        {
            
            

            //opens file in binary
            fin.open ( aFile.name, ios::binary );

            
            
            
            if ( fin.is_open() )
            {
                strcpy ( fileName, aFile.name );

                //calls function to identify the file. 
                identifyImage( fin, fileName );
            }
        }
   
    } while ( _findnext( dHandle, &aFile ) == 0) ;

    
    
    _findclose ( dHandle );
}
/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function's primary task is to identify the type of image. 
* It tests for GIF, BMP, PNG, or JPG image files by calling the 
* classification functions. After determining what type of image file it is,
* the function then calls the restore functions to rename the image file. 
*
* @param[in,out]  fin - file input stream
* @param[in]      fileName - the name of the file that we are checking
*
****************************************************************************/
void identifyImage( ifstream &fin, char fileName[] )
{
    //checks to see if it is a GIF
    if ( isGIF( fin ) == true )
    {
        restoreGIFImage( fin, fileName );
    }

    
    
    //checks to see if it is a BMP
    else if ( isBMP( fin ) == true )
    {
        restoreBMPImage( fin, fileName );
    }

    
    
    //checks to see if it is a PNG
    else if ( isPNG( fin ) == true )
    {
        restorePNGImage( fin, fileName );
    }

    
    
    //checks to see if it is a JPG
    else if ( isJPG( fin ) == true )
    {
        restoreJPGImage( fin, fileName );
    }

    
    
    else
    {
        fin.close();
    }
}

/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function seeks to restore a GIF image (a.k.a find the necessary infor-
* mation and use the necessary steps to rename the GIF image as 
* filename_widthxheight.gif). 
*
* @param[in,out]   fin - file input stream 
* @param[in]       fileName - name of the GIF image file
*
****************************************************************************/
void restoreGIFImage( ifstream &fin, char fileName[] )
{
    unsigned int height;
    unsigned int width;
    char dimens[_MAX_PATH + _MAX_PATH] = ""; //new file name with dimensions
    char widthHeight[100] = "";
    int test;
    


    strcpy( dimens, fileName );

    // '_' before the dimensions 
    strcat( dimens, "_" );
    
    
    
    GIFdimensions( fin, height, width );
    
    //call intToString to make the integer values of width and height character
    //values
    strcat( dimens, intToString( height, width, widthHeight ) );
    
    
    
    strcat( dimens, ".gif" );
    
    fin.close();

    
    
    //rename file
    test = rename( fileName, dimens );

    //check for success
    if ( test != 0 )
    {
        cout << "Unable to rename file. " << fileName << " ==> "
             << dimens << endl;
    }
}
/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function seeks to restore a BMP image (a.k.a find the necessary infor-
* mation and use the necessary steps to rename the BMP image as
* filename_widthxheight.bmp).
*
* @param[in,out]   fin - file input stream
* @param[in]       fileName - name of the BMP image file
*
****************************************************************************/
void restoreBMPImage( ifstream &fin, char fileName[] )
{
    unsigned int height;
    unsigned int width;
    char dimens[_MAX_PATH + _MAX_PATH] = ""; //new file name with dimensions
    char widthHeight[100] = "";
    int test;


    
    strcpy( dimens, fileName );

    // '_' before image's dimensions
    strcat( dimens, "_" );
    
    
    
    BMPdimensions( fin, height, width );
    
    //call intToString to make the integer values of width and height 
    //character values
    strcat( dimens, intToString( height, width, widthHeight ) );

    
    
    strcat( dimens, ".bmp" );

    fin.close();

    
    
    //rename file
    test = rename( fileName, dimens );
    
    //test for rename success
    if ( test != 0 )
    {
        cout << "Unable to rename file. " << fileName << " ==> "
            << dimens << endl;
    }
}
/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function seeks to restore a PNG image (a.k.a find the necessary infor-
* mation and use the necessary steps to rename the PNG image as
* filename_widthxheight.png
*
* @param[in,out]   fin - file input stream
* @param[in]       fileName - name of the PNG image file
*
****************************************************************************/
void restorePNGImage( ifstream &fin, char fileName[] )
{
    unsigned int height;
    unsigned int width;
    char dimens[_MAX_PATH + _MAX_PATH] = ""; //new file name with dimensions
    char widthHeight[100] = "";
    int test;


    
    strcpy( dimens, fileName );

    // '_' before dimensions
    strcat( dimens, "_" );
    
    
    
    PNGdimensions( fin, height, width );
    
    //call intToString to make the integer values of width and height 
    //character values
    strcat( dimens, intToString( height, width, widthHeight ) );

    
    
    //add extension
    strcat( dimens, ".png" );

    fin.close();

    
    
    //rename
    test = rename( fileName, dimens );

    //test for success 
    if ( test != 0 )
    {
        cout << "Unable to rename file. " << fileName << " ==> "
            << dimens << endl;
    }
}
/*************************************************************************//**
* @author Nathaniel Fagrey.
*
* @par Description:
* This function seeks to restore a JPG image (a.k.a find the necessary infor-
* mation and use the necessary steps to rename the JPG image as
* filename.jpg).
*
* @param[in,out]   fin - file input stream
* @param[in]       fileName - name of the JPG image file
*
****************************************************************************/
void restoreJPGImage( ifstream &fin, char fileName[] )
{
    char newFileName[_MAX_PATH + _MAX_PATH]; //new file name with dimensions
    int test;


    
    strcpy( newFileName, fileName );

    //add extension 
    strcat( newFileName, ".jpg" );
    
    fin.close();

    
    
    //rename 
    test = rename( fileName, newFileName );

    //test for success
    if ( test != 0 )
    {
        cout << "Unable to rename file. " << fileName << " ==> "
            << newFileName << endl;
    }
}

/*************************************************************************//**
* @author Nathaniel Fagrey
*
* @par Description:
* This function takes the height and width of a particluar image and 
* converts it to a string that will later be used to remane an image with its
* dimensions. 
* 
* @param[in]     height  - The height of a image in pixels.
* @param[in]     width - The width of an image in pixels. 
*
* @returns       widthHeight - dimensions of the image converted to characters       
****************************************************************************/
char *intToString( unsigned int height, unsigned int width, 
    char widthHeight[] )
{
    int charcNum;
    int i = 0;
    
    do
    {
        //get remainder of height
        charcNum = height % 10;
    
        //store the character equivalent of that remainder
        widthHeight[i] = ( charcNum + 48 );
        
        ++i;
       
        height /= 10;
    
    } while ( height >= 1 );

    
    
    // 'x' between width and height
    strcat( widthHeight, "x" );
    
    ++i;
    
    
    
    do
    {
        //get remainder of width
        charcNum = width % 10;

        //store that remainder as the character equivalent
        widthHeight[i] = ( charcNum + 48 );

        ++i;

        width /= 10;

    } while ( width >= 1 );
    
    
    
    //reverse string
    strrev( widthHeight );

    return widthHeight;
}

