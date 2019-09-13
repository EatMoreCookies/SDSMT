/***************************************************************************//**
 * @file callbacks.cpp
 ******************************************************************************/
#include "callbacks.h"

/***************************************************************************//**
 * @brief the display event callback function
 ******************************************************************************/
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   eventDispatch(Event());
   glFlush();
}

/***************************************************************************//**
 * @brief The keyboard event callback function
 *
 * @param[in] key - the key that was pressed
 * @param[in] x - the x-coordinate of the window where the key was pressed
 * @param[in] y - the y-coordinate of the window where the key was pressed
 ******************************************************************************/
void keyboard(const byte key, const int x, const int y)
{
   if (key == ESCAPE_KEY)
      glutLeaveMainLoop();
   else
      eventDispatch(Event(key, x, y));
}

/***************************************************************************//**
 * @brief The reshape event callback function
 *
 * @param[in] w - the new window width
 * @param[in] h - the new window height
 ******************************************************************************/
void reshape(const int w, const int h) {
    glLoadIdentity();           // initialize transformation matrix
    gluOrtho2D(0.0,w,0.0,h);
    glViewport(0,0,w,h);        // adjust viewport to new window
    glutPostRedisplay();
}
