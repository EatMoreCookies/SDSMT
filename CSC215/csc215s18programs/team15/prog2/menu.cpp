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
 * @param[in,out]      ourMenu - a menu from the menu class.
 *
 ****************************************************************************/
void setUpMainMenu( menu &ourMenu ) 
{
    int i;
    
    //our menu
    vector<string> v = { "Add a Subtitle frame", "Remove a frame", 
                         "Retrieve a frame", "Update a frame", 
                        "Print subtitles to screen", "Print range of "
                        "subtitles", "Exit" };


    
    //adds all the menu items to theMenu
    for ( i = 0; i < v.size(); ++i )
    {
        ourMenu.addMenuItem( v.at(i), i );
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
 ****************************************************************************/
void menu::printMenu()
{
    int i;

    
    
    //prints menu
    for ( i = 0; i < theMenu.size(); ++i )
    {
        cout << i + 1 << ").  " << theMenu.at(i) << endl;
    }

}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function gets the user's choice on what menu item he or she would like 
 * to do. The function prints the main Menu and prompts the user to enter a 
 * choice. If the user does not enter a choice that is between 1 and 7 
 * inclusive, the function will output an error message and prompt again until
 * the user enters a valid option. 
 * 
 * @param[in]      withMenu - a boolean value that is true by default.
 *
 * @returns choice user's first valid menu choice
 *
 ****************************************************************************/
int menu::getMenuSelection( bool withMenu )
{
    int choice;
    menu mainMenu;

    
    //print menu and get first selection 
    printMenu();

    cout << "Enter a selection: ";

    cin >> choice;

    
    
    //make sure that choice is valid
    while ( choice < 1 || choice > 7 )
    {
        cout << "Invalid option" << endl << endl;
    
        printMenu();

        cout << "Enter selection: ";
        
        cin >> choice;
    }

    
    
    //clear menu once it is used as to avoid doubling menu items as the program
    //prints the menu again
    theMenu.clear();
    
    return choice;
}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function sets up the sub menu that is displayed when the user chooses
 * to exit. One option is to save the SRT file over the top of the original 
 * file. The other option is to exit without saving. The sub menu is created 
 * by calling the addMenuItems and the printMenu functions. The user will 
 * continued to be prompted until a valid choice is entered. 
 * 
 * @param[in,out]  subMenu - a menu for the subMenu. 
 * @param[in]      fileName - the name of the SRT file
 *
 * @returns choice the choice of the user for the submenu 
 *
 ****************************************************************************/
int setUpSubMenu( menu &subMenu, string fileName )
{
    int i;
    int choice;
    
    vector<string> v = { "Save to " + fileName + " and exit." ,
                        "Exit without saving. " };



    //use same function to add in sub menu items 
    for (i = 0; i < v.size(); ++i)
    {
        subMenu.addMenuItem( v.at(i), i );
    }


    
    //prints sub memu
    subMenu.printMenu();

    cout << "Enter selection: ";
        cin >> choice;

  
   
    //make sure choice is valid
   while ( choice != 1 && choice != 2 )
   {
       cout << "Invalid option. " << endl;

       cout << "Enter selection: ";
        cin >> choice;
   }

   
   
   return choice;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * The destructor for the menu class. It clears theMenu of any menu items. 
 * 
 ****************************************************************************/
menu::~menu()
{
    theMenu.clear();
}
