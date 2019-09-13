/***************************************************************************//**
@file
@brief A function used to consolidate various openGL event calls
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include "util.h"
#include "TreeDisplay.h"

/// Symbolic constants for the backspace and escape keys.
static const int BSP = 8;
static const int ESC = 27;

/***************************************************************************//**
@author Paul Hinker

@par Description:
This function gets called when an event happens in callbacks. Depending on the
enum and data passed in it will do different things.  For this simple 
application there are only three events.  The initial event (fired from the
init code in main), DISPLAY events (fired by things like window resizing and
calls to glutPostRedisplay()), and KEYBOARD events (keys are accumulated into
a number until the character return is entered)

@param[in] event - structure that contains data about the event to handle
*******************************************************************************/
void eventDispatch(const Event & event) 
{
    static TreeDisplay treeDisplay;

	switch (event.event) {
		case INIT: {
			break;
		}
		case DISPLAY: {
            treeDisplay.draw();
			break;
		}
		case KEYBOARD:
        {
           treeDisplay.addToNodeVal(event.key);
           glutPostRedisplay();
        }
			break;
	}
}
