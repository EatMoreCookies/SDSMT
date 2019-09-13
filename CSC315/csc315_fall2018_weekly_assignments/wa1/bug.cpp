#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
   srand(time(NULL));
   int x, y;

   x = rand() % 100;
   y = rand() % 2;

   int z = x / y;

   cout << "Answer = " << z << endl;
   return 0;
} 
