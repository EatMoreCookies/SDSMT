#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <iostream>
#include <queue>
#include "util.h"
#include "node.h"
#include <GL/freeglut.h>

using namespace std;

#define ESCAPE_KEY 27

void insert(Node*& root, int data);
void DrawFilledRectangle();

void display(void);
void keyboard(const byte key, const int x, const int y);
void initOpenGL(int ncols, int nrows);
void reshape(const int w, const int h);

#endif
