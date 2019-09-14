/****************************************************************************//**
* @file file contains several functions that we wanted seperate 
********************************************************************************/
#include"bacon.h"

/*************************************************************************//**
 * @author Nathaniel Fagrey
 *
 * @par Description: 
 * This function prints a menu and gets the user choice on what they want to do
 * with the bacon game. 
 *
 * @return   actorName  - name of actor to find the shortest path to
 * @return   "histogram" - print the histogram
 * @return   "longest"   - find the longest shortest path
 * @return   "quit"    - quit bacon game
 *
 ****************************************************************************/
string menu ()
{
    string choice;
    string actorName;
    int i = 0;    
 
    //while ( choice != 1 && choice != 2 && choice != 3 && choice != 4 
    //		    && choice != 5 ) 
    do
    {
        
        //print menu    
        cout << endl << "Menu options. Please choose one" << endl;

        cout << "1). Find the Bacon Path for an actor: " << endl << "2). Display a histogram of actors: "
             << endl << "3). Print out the longest paths from starting actor: " << endl << "4). Display all actors" 
	     << " of a chosen Bacon Number" << endl
             << "5). Quit Bacon Game: " << endl << "Enter choice: ";
    
        //:w::cin.clear(); 
	//get user choice
        getline(cin, choice);
        

        
        //find out what to do.
        if ( choice == "1" )
        {
            cout << "Enter the name of your actor or actress: ";

	    cin.clear();

            getline(cin, actorName );
            
            return actorName;
        }

        else if ( choice == "2" )
        {
           //cin.clear();
           return "histogram";
        }
        else if ( choice == "3" )
        {
           //cin.clear();
           return "longest";
        }
        else if (choice == "5" )
        {
           //cin.clear();
           return "quit";
        }
	else if( choice == "4")
        {
           cin.clear();
           return "baconNum";
        }
     
        else
        {
           cout << endl << "Not a valid input. Please try again" << endl << endl;
           
        }
        cin.clear();
        
    } while(i == 0 );
   
      //stop the compiler from complaining
      return "MakeCompileHappy"; 
}


/*************************************************************************//**
 * @author Robert Minick
 *
 * @par Description:
 * This function will print to the screen a histrogram of bacon numbers and
 * an integer value of the number of actors with that bacon number
 *
 * @param[in]   baconNum    map holding actor string and bacon numbers
 * @param[in[   histogram[] array holding bacon count in array indecies
 * @return      INF         integer value of actors with bacon number of Infinity
 * 
 ****************************************************************************/
int histoGram(unordered_map<string, int> &baconNum, int histogram[])
{
   unordered_map<string,int>:: iterator mapItr;
   int INF = 0;

   // walk through baconNum map
   for ( mapItr = baconNum.begin(); mapItr != baconNum.end(); ++mapItr)
   {

      if (mapItr->second != INFINIT)
         ++histogram[mapItr->second];
      else
      ++INF;
   }


   return INF;
}

/*************************************************************************//**
 * @author Robert Minick
 *
 * @par Description:
 * This function will print all actors of a specific Bacon Number to the
 * screen
 *
 * @param[in]   baconNum    map holding key of actors and their bacon number
 * @param[in[   bn          variable holding bacon number
 *
 ****************************************************************************/
void outFile(unordered_map<string, int> &baconNum, int bn, string file)
{
   ofstream fout;
   int i =0;
   unordered_map<string, int> :: iterator mapItr;

   // attempt to open outfile
   fout.open(file);
   if(!fout)
   {
      cout << "Output file could not be opened" << endl;
      exit(0);
   }

   fout << "The following actors have a Bacon Number of: " << bn << endl;

   // walk through bn map
   for ( mapItr = baconNum.begin(); mapItr != baconNum.end(); ++mapItr)
   {
      if(mapItr->second == bn)
      {
         fout << setw(35) << left << mapItr->first;
         i++;

         if(i%5==0)
            fout << endl;
      }
   }
   fout.close();
}


/*************************************************************************//**
 * @author Robert Minick
 *
 * @par Description:
 * This function will print all actors of a specific Bacon Number to a
 * specified file as it is too large to print to monitor
 *
 * @param[in]   baconNum    map holding key of actors and their bacon number
 * @param[in[   bn          variable holding bacon number
 *
 ****************************************************************************/
void printBN(unordered_map<string, int> &baconNum, int bn)
{
   int i = 0;
   unordered_map<string, int> :: iterator mapItr, itr;

   cout << "The following actors have a Bacon Number of: " << bn << endl;

   // walk through bn map
   for ( mapItr = baconNum.begin(); mapItr != baconNum.end(); ++mapItr)
   {
      if(mapItr->second == bn)
      {
         cout << setw(35) << left << mapItr->first;
         i++;
      
         if(i%3==0)
            cout << endl;   
      }
   }
   cout << endl;
}
                                                                                                                                  

