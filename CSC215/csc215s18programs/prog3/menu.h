/*************************************************************************//**
 * @file
 * @brief header file for menu.cpp file
****************************************************************************/
#ifndef _MENU_H
#define _MENU_H

#include<string>
#include<vector>
#include<iostream>
#include<algorithm> 
#include<iomanip>
#include<vector>
using namespace std;


/*!* @brief this class allows access to all the functions that have to do with
menus in the program */
class menu
{
    public:
        menu();
        menu( vector<string> &menuList );
        menu( menu &aMenu );
        ~menu();

        bool addMenuItem( string item, int pos);
        
        bool removeMenuItem( int pos );
        bool updateMenuItem( string item, int pos );

        void printMenu( int size, int rowPos, int colPos );
        
        int getMenuSelection( bool withMenu, int &rowPos, int &colPos, 
            int &size );
        
        int size();
        void clear();

    private:
        vector<string> theMenu; /*!< this contains a menu */
                                

};


void setUpMainMenu( menu &myMenu );

int getSubMenu1( menu &myMenu, int rowPos, int colPos );

void getSubMenu2( menu &myMenu, int &rowPos, int &colPos, int &size );




#endif
