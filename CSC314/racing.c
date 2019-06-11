#include <stdio.h>


int quad(int x, int y )
{
  if ( x > 0)
    {
      //quad 1 or 4
      if ( y >0)
	return 1;

      else
	return 4;
      
    }

  else
    { 
      if (y > 0)
	return 2;

      else
	return 3;

    }

}


int main ()
{
  int x, y, q;

  scanf("%d%d", &x, &y);
  printf("&d\n", quad (x, y));


  return 0;
}
