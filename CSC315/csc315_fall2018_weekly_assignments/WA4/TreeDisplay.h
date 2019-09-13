/***************************************************************************//**
 * @file TreeDisplay.h
 ******************************************************************************/
#ifndef __TREEDISPLAY_H
#define __TREEDISPLAY_H
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include "node.h"

void insert(Node*& root, int val);

#define ENTER_KEY 13

using namespace std;

/***************************************************************************//**
 * @class TreeDisplay
 ******************************************************************************/
class TreeDisplay
{
   /// Value for the node
   string nodeVal;
   /// Root pointer
   Node *root;

public:
   /// Function to accumulate keys for a node value
   void addToNodeVal(char key);
   /// Draw the AVL tree
   void draw();
};

/// Width of the graphical node to draw
const int NODE_WIDTH = 20;
/// Height of the graphical node to draw
const int NODE_HEIGHT = 20;
/// Color of the graphical node to draw
const float color[] = {1.0, 1.0, 1.0};

/// Function to draw a filled rectangle at a given spot
void DrawFilledRectangle(int x1, int y1, int x2, int y2);
/// Function to draw a text at a given spot
void DrawTextString( const char *string, int x, int y);
/// Function to draw a line segment from point [x1,y1] to point [x2,y2]
void DrawLine(int x1, int y1, int x2, int y2);

#endif
