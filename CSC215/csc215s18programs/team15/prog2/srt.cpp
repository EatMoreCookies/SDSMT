/*************************************************************************//**
 * @file
 * @brief file that contains all functions related to the srtList class
****************************************************************************/
#include"srt.h"
#include"menu.h"


/** @brief values for the menu choice */
enum choices {
              
              INSERT = 1, /*!< contains the value 1 for the insert option */
              
              REMOVE,     /*!< contains the value 2 for the remove option */
              
              RETRIEVE,   /*!< contains the value 3 for the retrieve option */
              
              UPDATE,     /*!< contains the value 4 for the update option */
              
              PRINT_ALL,  /*!< contains the value 5 for the print all option */
              
              PRINT_RANGE,/*!< contains the value 6 for the print range
                          option */
              
              EXIT        /*!< contains the value 7 for the exit option */
};


/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This is the constructor for the srtList class. It sets headPtr to nullptr.
 * 
 ****************************************************************************/
srtList::srtList()
{
    headPtr = nullptr;
}


/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function makes sure that only two arguments were entered on the command
 * line. If less or more than two are entered, a usage statement is printed to 
 * the screen, false is returned, and the program is exited. 
 * 
 * @param[in]      num - number of arguments on the command line 
 *
 * @returns true correct number of arguments on the command line
 * @returns false incorrect number of arguments on the command line
 ****************************************************************************/
bool checkArgcVal( int num )
{
    //check argument number
    if ( num != 2 ) 
    {
        cout << "Incorrect number of arguments entered. " << endl
            << "In order to use this program, you must specify, " << endl
            << "on the command line, the one srt file that you would like "
            "to edit. " << endl;
            
        return false;
    }

    
    
    else
      
       return true;

}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function reads in the frames from the SRT file that was given on the
 * command line. Each frame in the SRT file is seperated by a blank line. The
 * frame number of each frame is not saved as these frame numbers will change
 * when the file is edited. If an empty SRT file is given, the function will 
 * not add anything to the linked list. If the file is not 
 * empty, the function will insert these frames into an empty linked list. 
 * 
 * @param[in,out]  fin - file stream object
 * @param[in,out]  myinsert - my linked list 
 * 
 ****************************************************************************/
void readInList( ifstream &fin, srtList &myinsert ) 
{                                                         
 
    string useless = "";
    string startTime;
    string endTime;
    string caption = "";
  
    
    
    while ( !fin.eof() )
    {
         
         getline( fin, useless );
        
         getline( fin, startTime, ' ' );

         //this would be the arrow seperating the start and end time
         getline( fin, useless, ' ' );

         getline( fin, endTime );

         getline( fin, useless );
         
         
         while ( !useless.empty() )
         {
             caption += useless;

             caption += '\n';

             getline( fin, useless );
         }

         
         
         //erases the extra new line in caption, but only if caption is not 
         //empty
         if ( !caption.empty() )
            caption.erase(caption.size() - 1, 1);
         
         
         fin.ignore();


         //insert this frame into the linked list
         myinsert.insert( startTime, endTime, caption );
    
         //clear caption for next one
         caption.clear();
    }
}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function takes the user's choice, found in main, and calls the 
 * appropriate function for it: insert, remove, retrieve, update, print, print 
 * range, and exit. A switch statement and enum is used to keep track of these.
 * This function will also prompt the user for the necessary information for 
 * these functions.
 * 
 * @param[in]      choice - a user's menu choice
 * @param[in,out]  linkedList - the linked list containing the frames
 * @param[in]      file - the SRT file name
 * @param[in,out]  fout - ofstream file object
 * 
 * @returns false unable to complete menu action
 * @returns true able to complete menu action
 *
 ****************************************************************************/
bool GetFunctions( int choice, srtList &linkedList, string file,
    ofstream &fout )
{
    string srtFile, startTime, endTime, caption;
    
    
    //for the submenu
    menu subMenu;

    int frameNum;
    int subMenuChoice;
    int startFrame, endFrame;
    
    
    
    switch ( choice )
    {
    case INSERT:

        cin.ignore();

        cout << "Enter a start time for the frame insertion: ";
            getline( cin, startTime );


        cout << endl << "Enter an ending time for the frame insertion: ";
            getline( cin, endTime );


        cout << endl << "Enter the caption you would like to insert: ";
            getline( cin, caption );


        
        //validate time
        if ( !validateTime( startTime ) || !validateTime( endTime ) ||
            startTime >= endTime || caption.empty() )
        {
            cout << "Invalid times entered or caption was empty. " << endl;
    
            return false;
        }
        
    
    

        //calls insert and checks for success
        if ( !linkedList.insert( startTime, endTime, caption ) )
        {
            cout << "Unable to insert frame. " << endl;

            return false;

        }

        break;

    case REMOVE:

        cout << "Enter the frame number you would like to remove: ";
            cin >> frameNum;

        
        
        //calls remove and checks for success
        if ( !linkedList.remove( frameNum ) )
        {
            cout << "Unable to remove frame " << frameNum << " from list. "
                << endl;

            return false;
        }

        break;

    case RETRIEVE:

         cout << "Enter the frame number you would like to retrieve: ";
            cin >> frameNum;
        
        
        
        //calls retrieve and checks for success    
        if ( !linkedList.retrieve( frameNum, startTime, endTime, caption ) )
        {
            cout << "Unable to retrieve frame " << frameNum << " from list. "
                << endl;

            return false;
        }

        break;

    case UPDATE:

        cout << "Enter the frame number you would like to change: ";
            cin >> frameNum;

        cout << endl;

        
        if ( !linkedList.retrieve( frameNum, startTime, endTime, caption ) )
        {
            cout << "Unable to update frame " << frameNum << " from list. "
                << endl;

            return false;
        }


       
        cin.ignore();

        
        cout << "Enter the new caption for this frame: ";
            getline( cin, caption );

        
        
        //calls update and checks for success
        if ( !linkedList.update( frameNum, caption ) )
        {

            cout << "Unable to update frame " << frameNum << " from list. "
                << endl;

            return false;

        }

        break;

    case PRINT_ALL:

        //calls print function
        linkedList.printSrt( cout );
        
        break;

    case PRINT_RANGE:
        
        cout << "Enter the start frame to be printed: ";
            cin >> startFrame;

        cout << "Enter the end frame to be printed: ";
            cin >> endFrame;
       
        
        //make sure that print range is successful
        if (!printRange(cout, linkedList, startFrame, endFrame))
        {
            cout << "Unable to print range. " << endl;

            return false;
        }
        
        break;

    case EXIT:

        //sets up sub Menu
        subMenuChoice = setUpSubMenu( subMenu, file );

       
        
        //if choice is one, print edited SRT file over top of original
        if ( subMenuChoice == 1 )
        {
            fout.open( file );

            
            
            if( !fout.is_open() )
                return false;

            
            //prints to file
            linkedList.printSrt( fout );

            
            //close file
            fout.close();
        }
        
        break;

    }

    return true;
}
/*************************************************************************//**
 * @author Nathaniel Fagrey, Robert Parsons
 * 
 * @par Description: 
 * This function takes in three strings given by the user and inserts them into
 * the linked list. The times for the insertion are already validated when we
 * call the function. The function then inserts this new frame into the correct 
 * postion in the linked list by comparing the given times with those that are
 * already in the linked list.
 * 
 * 
 * @param[in]      startingTime - the start time of our new frame
 * @param[in]      endingTime - the ending time of our new frame
 * @param[in]      theCaption - the new caption that the user wants to add
 *
 * @returns false failed to do the insertion
 * @returns true successfully did the insertion 
 * 
 ****************************************************************************/
bool srtList::insert( string startingTime, string endingTime,
    string theCaption )
{
    node *temp;
    node *curr;
    node *prev;
    
    
    curr = headPtr;
    prev = headPtr;

    
    
    //for when calling the insertion but having an empty file
    if ( startingTime.empty() )
       return false;
    
    
    
    //create new node
    temp = new ( nothrow ) node;

    if ( temp == nullptr )
        return false;

    
   
    //inserting into empty list
    if ( headPtr == nullptr )
    {
        temp->startTime = startingTime;

        temp->endTime = endingTime;

        temp->caption = theCaption;

        temp->next = nullptr;

        headPtr = temp;

        return true;
    }
    
    

    //insertion into front of list
    if ( endingTime < curr->startTime )
    {
        temp->next = curr;

        temp->startTime = startingTime;

        temp->endTime = endingTime;

        temp->caption = theCaption;

        headPtr = temp;
       
        return true;
    }
    
    
    
    curr = curr->next;

    

    //traverse through the linked list looking where to place the new node
    while ( curr != nullptr && ( !( startingTime > prev->endTime 
        && endingTime < curr->startTime ) ) )
    {
        prev = curr;

        curr = curr->next;

    }
    
   
    
    //insertion at end of list
    if ( curr == nullptr && startingTime > prev->endTime )
    {
        temp->next = nullptr;

        temp->startTime = startingTime;

        temp->endTime = endingTime;

        temp->caption = theCaption;

        prev->next = temp;
       
        return true;
    }

    
    
    //make sure that when we hit the end of the list, the starting time is 
    //greater than the ending time of the last node
    else if (curr == nullptr && startingTime <= prev->endTime)
        return false;
    
    
   
    //insertion into the middle
    temp->next = curr;

    temp->startTime = startingTime;

    temp->endTime = endingTime;

    temp->caption = theCaption;

    prev->next = temp;

    return true; 
}

/*************************************************************************//**
 * @author Nathaniel Fagrey, Joseph Howell
 * 
 * @par Description: 
 * This function makes sure that the time given by the user for the frame 
 * insertion is in the valid time format of HH:MM:SS,mili where mili is three
 * digits. This functions also checks to make sure that the time is only 12 
 * characters long.
 * 
 * @param[in]      item - a time that what given by the user
 *
 * @returns false invalid time given
 * @returns true valid time given
 * 
 ****************************************************************************/
 bool validateTime( string item ) 
{
    string::iterator it;
    int j = 0;

    
    
    //check item size
    if( item.size() != 12 )
        return false;
  
   
    
    //makes sure that item is in the exact format of HH:MM:SS,mmm
    for ( it = item.begin(); j < item.size(); ++it )
    {
        
        
        //checks for the digits
        if ( j == 0 || j == 1 || j == 3 || j == 4 || j == 6 || j == 7 ||
            j == 9 || j == 10 || j == 11 )
        {
            if( !isdigit( *it ) )
                return false;
        }

        
        
        //checks for the colons
        if ( j == 2 || j == 5 )
        {
            if ( *it != ':')
                return false;
        }
        
        
        
        //checks for the comma
        if( j == 8 && *it != ',')
            return false;
       
       
        
        ++j;
    }


    
    return true;
}
/*************************************************************************//**
* @author Nathaniel Fagrey, Robert Parsons
* 
* @par Description: 
* This function prints the linked list that we created to either the screen or 
* to the original SRT file. It also outputs the number of the frame that it is 
* on. 
* 
* @param[in]      out - an ostream object
* 
****************************************************************************/
void srtList::printSrt( ostream &out )
{
    node *curr = headPtr;
    int frameNo = 1;

   
    
    if ( headPtr == nullptr )
        return;
    
    
    
    //traverses through the list
    while( curr != nullptr )
    {
        
        out << frameNo << endl;
        out << curr->startTime << " --> " << curr->endTime << endl;
        out << curr->caption << endl << endl;
        
       curr = curr->next;
       
       frameNo++;
    }         
}

/*************************************************************************//**
 * @author Bobby Parsons
 * 
 * @par Description: 
 * This function returns the size of the SRT list. It steps through the whole
 * list to calculate the size and then returns the result.
 * 
 * @returns  size number of nodes in the SRT list
 *
 ****************************************************************************/
int srtList::size()
{
    node *curr = headPtr;
    int size = 0;

    
    
    if ( headPtr == nullptr )
        return 0;
    
    
    
    while (curr != nullptr)
    {
        curr = curr->next;
        size++;
    }

    return size;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function will take the frame that the user gives, print it to the 
 * the screen and allow the user to replace the old caption with a new one.  
 * 
 * @param[in]      frame - the frame to be updated
 * @param[in]      theCaption - the new caption that the user wants in the 
 *                              frame. 
 * 
 * @returns false failed to update frame 
 * @returns true able to update frame
 * 
 ****************************************************************************/
bool srtList::update( int frame, string theCaption )
{
    node *curr = headPtr;
    int listSize;
    int i = 1;

    
    
    if (theCaption.empty())
        return true;
    
    
    
    //gets list size 
    listSize = size();

    
    
    //check for empty list
    if (listSize < 1)
        return false;

    
    
    //makes sure that the frame is actually in the list
    if ( frame < 1 || frame > listSize )
        return false;
   
    
    
    //traverse though the list looking for the frame to insert
    while ( i != frame && curr != nullptr )
    {
        ++i;

        curr = curr->next;
    }
   
    
    
    //update frame
    curr->caption = theCaption;
    
    return true;
}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 *
 * @par Description: 
 * This function removes a frame that the user specifies from the list. The
 * count of the number of frames in the list is affected. 
 * 
 * @param[in]      frame - the frame that the user wants to remove
 * 
 * @returns false failed to remove frame
 * @returns true successfully removed the frame.  
 * 
 ****************************************************************************/
bool srtList::remove( int frame )
{
    node *curr = headPtr;
    node *prev = headPtr;
    
    int i = 1;

    
    
    //check for empty list 
    if ( headPtr == nullptr )
        return false;

    
    
    //validate frame number
    if ( frame < 1 || frame > size() )
        return false;
    
    
    
    // remove from the begining of the list
    if ( frame == 1 )
    {
        headPtr = curr->next;

        delete curr;

        return true;
    }
    
    
   
    //traverse through the list
    while ( curr != nullptr && i != frame )
    {
        prev = curr;

        curr = curr->next;

        ++i;
    }
        
    
    
    //remove frame
    prev->next = curr->next;

    delete curr;

    return true;
}
/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function will retrieve any frame that the user specifies and print it
 * to the screen. 
 * 
 * @param[in]      frame - the frame to be retrieved
 * @param[in,out]  startingTime - will hold the starting time for that frame
 * @param[in,out]  endingTime - will hold the endingTime for that frame.
 * @param[in,out]  theCaption - will contain the caption for that frame. 
 * 
 * @returns false unable to retrieve frame
 * @returns true able to retrieve frame 
 * 
 ****************************************************************************/
bool srtList::retrieve( int frame, string &startingTime, string &endingTime,
    string &theCaption )
{
    node *curr = headPtr;
    int i = 1;
    
    
    //check for empty list
    if ( headPtr == nullptr )
        return false;

    
    
    
    //makes frame is in list
    if ( frame < 1 || frame > size() )
        return false;

    
    
    //traverse the list
    while ( i != frame && curr != nullptr )
    {
        curr = curr->next;

        ++i;
    }

    
    
    //get startingTime, endingTime, and theCaption from the list
    startingTime = curr->startTime;

    endingTime  = curr->endTime;

    theCaption = curr->caption;
    
    
    
    //print frame
    cout << "Frame number " << frame << endl << startingTime << " --> " 
        << endingTime << endl << theCaption << endl;
        
    return true;
}



/*************************************************************************//**
 * @author Bobby Parsons
 * 
 * @par Description: 
 * This function will print out a range of subtitles from the SRT list to the
 * specified output stream.
 * 
 * @param[in,out]      out - Output stream (cout, cerr, fout, etc.)
 * @param[in,out]      srt - SRT List
 * @param[in]          startFrame - Start Frame
 * @param[in]          endFrame - End Frame
 * 
 * @returns false Invalid arguments.
 * @returns true Ran successfully. 
 *
 ****************************************************************************/
bool printRange(ostream & out, srtList & srt, int startFrame, int endFrame)
{
    string caption, startTime, endTime;
    int frameNo;
    
    if ( startFrame < 1 || endFrame < 1 || endFrame > srt.size() || 
        startFrame > endFrame)
        return false;
    
    
    
    for (frameNo = startFrame; frameNo <= endFrame; frameNo++) 
    {
        srt.retrieve(frameNo, startTime, endTime, caption);  
        cout << endl;
    }
    
    return true;
}

/*************************************************************************//**
 * @author Nathaniel Fagrey
 * 
 * @par Description: 
 * This function is the deconstructor for the srt class. It goes through the 
 * linked list deleting ever node, until headPtr == nullprt;
 * 
 ****************************************************************************/
srtList::~srtList()
{
    node *curr = headPtr;

    
    
    while ( headPtr != nullptr )
    {
        headPtr = curr->next;

        delete curr;

        curr = headPtr;
    }
}
