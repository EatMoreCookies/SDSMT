#include <iostream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;

struct Node
{
   int ID;
   int value;
   Node(int id, int val) : ID(id), value(val){}


 
  // You need to define a friend function for the << operator here
  friend ostream & operator<< (ostream &out, Node test)
  {
	cout << test.ID << endl << test.value << endl;
  }

  //Write the += operator here
	
  int  operator+= ( Node val1 )
  {
	val1.value = val1.value * 2;

	return val1.value;
  }

};


template<typename Container>
void initializeContainer(Container &container, int size)
{
   for (int i = 0 ; i < size ; i++)
      container.push_back(Node(i, size-i));
}

template<typename Container>
void removeEveryOther(Container &container)
{
#ifdef TIMING
   std::chrono::duration<double> elapsedTime;
   auto startTime = chrono::system_clock::now();
#endif

   auto itr = container.begin();
   while (itr != container.end())
   {
      itr = container.erase(itr);
      if (itr != container.end())
             itr++;
   }

#ifdef TIMING
   auto endTime = chrono::system_clock::now();
   elapsedTime = (endTime - startTime);
   cout << "Elapsed Time: " << elapsedTime.count() << endl;
#endif
}

template<typename Container>
void printOut(string name, Container&container)
{
   cout << name << endl;
   for (Node node : container)
      cout << node << endl;
}

int main()
{
   vector<Node> vecNode;
   list<Node> listNode;
   int size;

   cout << "Enter size to test:";
   cin >> size;

   if (size > 0)
   { 
      // Initialize the containers
      initializeContainer(vecNode, size);
      initializeContainer(listNode, size);

      // Add the value of the last item in the container to the first
      vecNode[0] += vecNode[size-1];
      listNode.front() += listNode.back();
      cout << "VecNode[0] = " << vecNode[0] << endl;
      cout << "ListNode.front() = " << listNode.front() << endl;

      // Remove every other item from the containers.  Compile with -DTIMING
      // to see the elapsed time in the function
      cout << "Vector:\n";
      removeEveryOther(vecNode);
      cout << "List:\n";
      removeEveryOther(listNode);

      // Compile with -DDEBUG to see the printout of the containers
#ifdef DEBUG
      printOut("VecNode", vecNode);
      printOut("ListNode", listNode);
#endif
   }
   return 0;
}
