#include<stdio.h>


int reverse(int x)
{
   int r = 0;
   
   do 
   {
       r  <<= 1;
       
       if ( x & 1 )
          r |= 1;

       x >>= 1;

   } while (x != 0);
   

   return r; 

}


int main()
{
        int n;

	scanf("%d", &n);
	n = reverse(n);
	printf("%d\n", n);


	return 0;
}
