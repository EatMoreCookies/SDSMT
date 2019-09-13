#ifndef _NODE_H
#define _NODE_H
#include<cmath>
#include"WA4.h"
#include<algorithm>
using namespace std;
struct Node
{
   int data;
   Node* left;
   Node* right;
   int ht;

   Node(int d, Node* l=nullptr, Node* r=nullptr, Node* p=nullptr, int h=0): data(d), left(l), right(r), ht(h) {}
};




#endif
