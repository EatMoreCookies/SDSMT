#include <iostream>
#include "callbacks.h"

using namespace std;

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   initOpenGL(1024, 500);
   glutMainLoop();
   return 0;
}

void initOpenGL(int ncols, int nrows) 
{
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowSize(ncols,nrows);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Tree Viewer - Enter integers followed by <return>");

    glClearColor(0.0,0.0,0.0,0.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
}
