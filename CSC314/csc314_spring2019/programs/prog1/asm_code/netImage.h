#ifndef NETIMAGE_H
#define NETIMAGE_H
#include <stdio.h>
#include<stdlib.h>

typedef struct 
{
  unsigned char min;
  unsigned char max;
} minMax;

typedef enum
  {
    BRIGHTEN, NEGATE,SHARPEN,SMOOTH,GRAYSCALE,CONTRAST,SUBSAMPLE,
    BLEND,BINARY,ASCII
  } op_t;

typedef struct op_list_struct{
  op_t operation;
  char *argument;
  struct op_list_struct *next;
}op_list;

op_list * add_op(op_list* list,op_t operation, char *argument);

typedef struct blend_list_struct{
  char *filename;
  char *strength;
  struct blend_list_struct *next;
}blend_list;

blend_list * add_file(blend_list* list,char *strength, char *filename);


typedef struct{
  unsigned char red, green, blue;
}rgbpixel;


typedef struct
{	
  char  magicNumber;      // type of net image
  char * comment;         // the comments
  int bpp;                // the number of bits per pixel
  int rows;               // number of rows
  int cols;               // number of cols
  rgbpixel **image;
  unsigned char **grayimage;
}netImage;

netImage *readImage(FILE *inf);
void writeImage(FILE *inf, netImage *image);

void brightenImage( netImage *image, char *arg);
void negateImage( netImage *image);
void smoothImage( netImage *image);
void sharpenImage( netImage *image);
void contrastImage( netImage *image);
void subsampleImage( netImage *image, char *arg);
minMax grayscaleImage( netImage *image);
netImage * blendImages(blend_list *files);
rgbpixel ** allocate_struct_array (int rows, int cols );
rgbpixel **allocate_asm_struct(int rows, int cols);
rgbpixel **fixSharpenBorders(rgbpixel **tmp, int rows, int cols );

int crop( int value );

#endif
