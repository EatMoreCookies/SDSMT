#include "TreeDisplay.h"

/***************************************************************************//**
 * @brief Member function to add a Node
 *
 * @param[in] key - The key that was pressed
 ******************************************************************************/
void TreeDisplay::addToNodeVal(char key)
{
   // If the key was not the enter key, accumulate the value
   if (key == ENTER_KEY)
   {
      int val;
      stringstream stream1;
      stream1.str(nodeVal);
      stream1 >> val;
      insert(root, val);
      nodeVal.clear();
      glutSetWindowTitle("Tree Viewer - Enter integers followed by <return>");
   }
   else
   {  
      nodeVal += key;
      glutSetWindowTitle(nodeVal.c_str());
   }
}
/***************************************************************************//**
 * @brief the display event callback function
 *
 * @param[in] root - The node pointer to the subroot to calculate the height
 ******************************************************************************/
int getHeight(Node* root)
{
   if (root == nullptr) return -1;

   return max(getHeight(root->left), getHeight(root->right)) + 1;
}

/***************************************************************************//**
 * @brief Draw a node and the line connecting it to its parent
 *
 * @param[in] x - The window x-coordinate to draw the node
 * @param[in] y - The window y-coordinate to draw the node
 * @param[in] root - Node pointer for the node to draw
 * @param[in] depth - Integer describing the depth of the node
 ******************************************************************************/
void drawNode(int x, int y, Node* root, int depth)
{
   if (root == nullptr) return;

   stringstream ss;
   ss << root->data << "(" << root->ht << ")";
   DrawTextString(ss.str().c_str(), x, y);
   if (root->left != nullptr)
   {
      drawNode(x - (256 >> depth), y - 64, root->left, depth+1);
      DrawLine(x, y, x-(256 >> depth), y-64);
   }
   if (root->right != nullptr)
   {
      drawNode(x + (256 >> depth), y - 64, root->right, depth+1);
      DrawLine(x, y, x+(256 >> depth), y-64);
   }
   return;
}

/***************************************************************************//**
 * @brief Function to start the drawing of the treee
 ******************************************************************************/
void TreeDisplay::draw()
{
   int xs = glutGet(GLUT_WINDOW_WIDTH) / 2;
   int ys = glutGet(GLUT_WINDOW_HEIGHT) - 30;
   drawNode(xs, ys, root, 0);
}

/***************************************************************************//**
 * @brief Draw a filled rectangle
 *
 * @param[in] x1 - starting x-coordinate of the rectangle
 * @param[in] y1 - starting y-coordinate of the rectangle
 * @param[in] x2 - ending x-coordinate of the rectangle
 * @param[in] y2 - ending y-coordinate of the rectangle
 ******************************************************************************/
void DrawFilledRectangle(int x1, int y1, int x2, int y2)
{
    glColor3fv( color );
    glBegin( GL_POLYGON );
    glVertex2f( x1, y1 );
    glVertex2f( x2, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x1, y2 );
    glEnd();
    glFlush();
}

/***************************************************************************//**
 * @brief Draw a text string at a location
 *
 * @param[in] string - pointer to a character array of characters
 * @param[in] x - x-coordinate to start the text drawing
 * @param[in] y - y-coordinate to start the text drawing
 ******************************************************************************/
void DrawTextString( const char *string, int x, int y)
{
    glColor3fv( color );
    glRasterPos2i( x, y );
    while ( *string )
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *string++ );
}

/***************************************************************************//**
 * @brief Draw a line from one point to another
 *
 * @param[in] x1 - x-coordinate of the starting point of the line segment
 * @param[in] y1 - y-coordinate of the starting point of the line segment
 * @param[in] x2 - x-coordinate of the end point of the line segment
 * @param[in] y2 - y-coordinate of the end point of the line segment
 ******************************************************************************/
void DrawLine(int x1, int y1, int x2, int y2)
{
    glColor3fv(color);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

