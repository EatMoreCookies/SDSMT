#include <stdlib.h>
#include <netImage.h>

void sharpenImage( netImage *image)
{
  int i = 1;
  int j = 1;
  int rows = image->rows;
  int cols = image->cols;
  rgbpixel **rgbImage = image->image;
  rgbpixel **tmp;

  tmp = allocate_asm_struct(rows, cols);


    
do
{     
      
	tmp[i][0] = tmp[i][1];
	tmp[i][cols-1] = tmp[i][cols-2];

      if ( i < cols - 1 )
      {
	 tmp[0][i] = tmp[1][i];
	 tmp[rows-1][i] = tmp[rows-2][i];
      }
	
      j = 1;

      do
      {
	tmp[i][j].red = crop( 5*rgbImage[i][j].red -
			      rgbImage[i-1][j].red -
			      rgbImage[i][j-1].red -
			      rgbImage[i][j+1].red -
			      rgbImage[i+1][j].red);
	tmp[i][j].green = crop( 5*rgbImage[i][j].green -
			      rgbImage[i-1][j].green -
			      rgbImage[i][j-1].green -
			      rgbImage[i][j+1].green -
			      rgbImage[i+1][j].green);
	tmp[i][j].blue = crop( 5*rgbImage[i][j].blue  -
			      rgbImage[i-1][j].blue -
			      rgbImage[i][j-1].blue -
			      rgbImage[i][j+1].blue -
			      rgbImage[i+1][j].blue);
	++j;
	} while ( j < cols -1 );

	++i;
} while ( i < rows - 1 ); 
 /* fix up the borders */
  tmp[0][0] = tmp[1][1];
  tmp[0][cols-1] = tmp[1][cols-2];
  tmp[rows-1][0] = tmp[rows-2][1];
  tmp[rows-1][cols-1] = tmp[rows-2][cols-2];
  
  image->image=tmp;
}
