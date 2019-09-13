#ifndef WA4_H
#define WA4_H
//#include "node.h"

#define NODE_HEIGHT(n) (!n ? -1 : n->ht)
class Node;
void insert(Node* & t, int val);
int height(Node* t);
void balance( Node* &t);
void rotateWithLeftChild ( Node* &t );
void rotateWithRightChild( Node* &t );
void doubleWithLeftChild( Node* &t );
void doubleWithRightChild ( Node* &t );
#endif
