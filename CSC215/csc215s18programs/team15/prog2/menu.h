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

        void printMenu();
        int getMenuSelection( bool withMenu = true );
        int size();
        void clear();

    private:
        vector<string> theMenu; /*!< this contains a menu */
                                

};


void setUpMainMenu(menu &outMenu);

int setUpSubMenu(menu &subMenu, string FileName);



#endif
