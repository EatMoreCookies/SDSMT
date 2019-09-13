#include <iostream>
#include "node.h"
#include"WA4.h"
using namespace std;

int height(Node *);

void insert(Node*& root, int data)
{
   if (root == nullptr)
   { 
       root = new Node(data); 
      // return;
   }


   else if (data < root->data)
      insert(root->left, data);
   else
      insert(root->right, data);   

   int leftHeight = height(root->left);
   int rightHeight = height(root->right);
   root->ht = max(leftHeight,rightHeight) + 1;

   balance ( root );	

}



int height(Node *node)
{
   if ( node == nullptr)
      return -1;
   return node->ht;
}

static const int ALLOWED_IMBALANCE = 1;

void balance( Node *&t )
{
      if ( t == nullptr )
            return;

    //left case
    if ( height(t->left) - height(t->right)    >  ALLOWED_IMBALANCE )
            if ( height(t->left->left) >=  height(t->left->right) )
               rotateWithLeftChild( t );


            else
               doubleWithLeftChild( t );


  
    //right case;
    else
        if ( height(t->right ) - height(t->left) > ALLOWED_IMBALANCE )
             if ( height(t->right->right) >= height(t->right->left ) )
                    rotateWithRightChild( t );
             else
              doubleWithRightChild( t );

                     
}



void rotateWithLeftChild( Node * &t )
{
      Node *temp = t->left;
      t->left = temp->right;
      temp->right = t;

      t->ht = max( height( t->left), height( t->right ) ) + 1;
      temp->ht = max( height(temp->left), height(temp->right) ) + 1;

      t = temp;
}

void rotateWithRightChild( Node *& t)
{
     Node *temp = t->right;
     t->right = temp->left;
     temp->left = t;
    
     t->ht = max( height( t->right), height( t->left) ) + 1; 
     temp->ht = max( height( temp->right ), height(temp->left ) )+ 1;

     t = temp;
}


void doubleWithLeftChild ( Node * &t )
{
    rotateWithRightChild( t->left );
    rotateWithLeftChild( t );
}

void doubleWithRightChild ( Node * &t )
{
    rotateWithLeftChild( t->right );
    rotateWithRightChild( t );
}



