/*************************************************************************//**
 * @file
 * @brief contains all the functions that are related to the menu class
****************************************************************************/
#include"menu.h"


/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This is the constructor for the menu class. For this program is does not do
 * any initializing.
 *
 ****************************************************************************/
menu::menu()
{

}


/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function sets up the main menu for the user. It does this by calling 
 * the addMenuItem function that adds a vector of whatever menu to another menu
 * vector located in the menu class.
 * 
 * @param[in,out]      myMenu - a menu from the menu class.
 *
 ****************************************************************************/
void setUpMainMenu( menu &myMenu ) 
{
    int i;
    
    //our menu
    vector<string> v = { "Change board size from ", "Change starting "
                        "position from ", "Exit and Solve Tour " };
                         


    
    //adds all the menu items to theMenu
    for ( i = 0; i < v.size(); ++i )
    {
        myMenu.addMenuItem( v.at(i), i );
    }

}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function adds menu items to a vector that is located in the menu class.
 * 
 * @param[in]      item - a menu item. 
 * @param[in]      pos - position to insert the menu item (not for this 
 *                       program).
 * @returns true able to add item into the Menu
 * 
 ****************************************************************************/
bool menu::addMenuItem( string item, int pos )
{
    
    //adds menu items
    theMenu.push_back(item);

    return true;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function prints a menu to the screen. 
 *
 * @param[in] size - the size of our board
 * @param[in] rowPos - the row postion that we want to knight to start on
 * @param[in] colPos - the column postion that we want to knight to start on 
 *
 ****************************************************************************/
void menu::printMenu( int size, int rowPos, int colPos )
{

    
    cout << "1). " << theMenu.at(0) << size << "x" << size << "." 
            << endl;

    cout << "2). " << theMenu.at(1) << "[" << rowPos << "," << colPos << "]"  
            << endl;


    cout << "3). " << theMenu.at(2) << endl;

}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function gets the user's choice on what menu item he or she would like 
 * to do. The function prints the main Menu and prompts the user to enter a 
 * choice. If the user does not enter a choice that is between 1 and 3
 * inclusive, the function will output an error message and prompt again until
 * the user enters a valid option. 
 * 
 * @param[in]      withMenu - a boolean value that is true by default.
 * @param[in,out]  rowPos - the row postion that we want to knight to start on
 * @param[in,out]  colPos - the column postion that we want to knight to start     
 *                          on
 * @param[in,out]  size - size of the board                       
 *                 
 *
 * @returns choice user's first valid menu choice
 *
 ****************************************************************************/
int menu::getMenuSelection( bool withMenu, int &rowPos, int &colPos, 
    int &size )
{
    int choice = 99;
    
    
   
    //make sure that choice is valid
    while ( choice < 1 || choice > 3 )
    {
        printMenu( size, rowPos, colPos );

        cout << "Enter selection: ";
        
        cin >> choice;
        
        
        
        if ( ( choice >= 1 ) && ( choice <= 3 ) )
        {
            //clears menu of items;
            theMenu.clear();
            
            return choice;
        }
            
        
        
        cout << "Invalid option" << endl << endl;
    }
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function displays the submenu when the user selects the main menu option
 * of changing the size of the board. It will continue to prompt the user until
 * they enter a valid board size. 
 * 
 * @param[in,out]  mySubMenu - a menu for the subMenu. 
 * @param[in]      rowPos - the row postion that we want to knight to start on
 * @param[in]      colPos - the column postion that we want to knight to start 
 *                           on 
 *
 * @returns choice the choice of the user for the submenu 
 *
 ****************************************************************************/
int getSubMenu1( menu &mySubMenu, int rowPos, int colPos )
{
    int size;

    cout << "Enter the size of the NxN board (>3): ";
   
    cin >> size;

    
    
    //size must be greater than 3 and compatible with starting postions
    while ( size < 4 || size <= rowPos || size <= colPos )
    {
        cout << "Invalid board size entered. " << endl;

        cout << "Enter the size of the NxN board (>3): ";
   
        cin >> size;

    }

    
    
    cout << endl;
    
    return size;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function displays the submenu for when the user selects the main menu 
 * option of changing the starting postions of the knight. It will continue to 
 * prompt the user until they enter starting postions that are valid.
 * 
 * @param[in,out]      mySubMenu - a menu for the subMenu. 
 * @param[in,out]      rowPos - the row postion that we want to knight to start
 *                              on
 * @param[in,out]      colPos - the column postion that we want to knight to 
 *
 *                             start on
 *@param[in,out]       size - the size of out board. 
 *
 ****************************************************************************/
void getSubMenu2( menu &mySubMenu, int &rowPos, int &colPos, int &size )
{
    
    cout << "Enter your starting coordinates (x,y): ";

    cin >> rowPos >> colPos;

    
    //postions must be >= 0 and compatiable board size
    while ( ( rowPos >= size || colPos >= size ) || 
        ( rowPos < 0 || colPos < 0 ) )
    {
        cout << "Invalid starting position. " << endl;

        cout << "Enter your starting coordinates (x,y): ";

        cin >> rowPos >> colPos;
    
    }

    
    
    cout << endl;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * The destructor for the menu class. It does nothing for this program
 * 
 ****************************************************************************/
menu::~menu()
{
   
}