#include <iostream>
#include <stdlib.h>
#include <queue.h>

using namespace std;


int main()
{
  int i,rnum;
  queue q;
  
  srand(time(NULL));

  for(i=1;i<=100;i++)
    {
//      cout << i << "). "<< endl;
      //i=rand();
      q.enque(i);
      if(!(i%10))
	{
	  cout<<"Current queue:\n";
	  while(!q.isempty())
	    cout << q.deque(i) << endl;
	}
    }

  
  return 0;
}
