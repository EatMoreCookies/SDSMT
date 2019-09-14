#define CATCH_CONFIG_MAIN
#include "..\catch.hpp"
#include <iostream>
#include <string>
#include <sstream>

#include "unsortedDouble.h"

using namespace std;


TEST_CASE ( "Construtors" )
{
    unsortedDouble mylist;
    ostringstream forw;
    ostringstream back;
    
    REQUIRE ( mylist.isEmpty() == true );
    REQUIRE ( mylist.size() == 0 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( back, false );
    REQUIRE ( back.str() == "" );
}

TEST_CASE ( "Destructors" )
{
    unsortedDouble mylist;
    unsortedDouble mylist1;
    ostringstream forw;
    
    mylist.insert ( "word1" );
    mylist.insert ( "word2" );
    mylist.insert ( "word3" );
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
}

TEST_CASE ( "Clear" )
{
    unsortedDouble mylist;
    
    mylist.insert ( "word1" );
    mylist.insert ( "word2" );
    mylist.insert ( "word3" );
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
    mylist.clear();
    REQUIRE ( mylist.size() == 0 );
    REQUIRE ( mylist.isEmpty() );
}

TEST_CASE ( "Insert" )
{
    unsortedDouble mylist;
    unsortedDouble mylist1;
    ostringstream forw;
    ostringstream backw;
    
    mylist.insert ( "Harry" );      // Harry
    mylist.insert ( "Tom", 1 );     // Tom Harry
    mylist.insert ( "Dick", 2 );    // Tom Dick Harry
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
    
    SECTION ( "Empty" )
    {
        CHECK ( mylist1.isEmpty() );
        REQUIRE ( mylist1.insert ( "Some Word" ) == true );
        REQUIRE ( mylist1.size() == 1 );
        REQUIRE ( !mylist1.isEmpty() );
        
        mylist1.print ( forw );
        REQUIRE ( forw.str() == "Some Word" );
        mylist1.print ( backw, false );
        REQUIRE ( backw.str() == "Some Word" );
    }
    SECTION ( "Front" )
    {
        mylist1.insert ( "Harry" );                    // Harry
        REQUIRE ( mylist1.insert ( "Dick", 1 ) == true ); // Dick Harry
        REQUIRE ( mylist1.insert ( "Tom", 1 ) == true ); // Tom Dick Harry
        REQUIRE ( mylist1.insert ( "Ann", 1 ) == true ); // Ann Tom Dick Harry
        REQUIRE ( mylist1.insert ( "Paul",
                                   1 ) == true ); // Paul Ann Tom Dick Harry
        REQUIRE ( mylist1.insert ( "Roger",
                                   1 ) == true ); // Roger Paul Ann Tom Dick Harry
        CHECK ( mylist1.size() == 6 );
        
        mylist1.print ( forw );
        REQUIRE ( forw.str() == "Roger, Paul, Ann, Tom, Dick, Harry" );
        mylist1.print ( backw, false );
        REQUIRE ( backw.str() == "Harry, Dick, Tom, Ann, Paul, Roger" );
    }
    SECTION ( "Middle" )
    {
        CHECK ( mylist.size() == 3 );       // Tom Dick Harry
        REQUIRE ( mylist.insert ( "Ann", 2 ) == true ); // Tom Ann Dick Harry
        REQUIRE ( mylist.insert ( "Paul", 3 ) == true ); // Tom Ann Paul Dick Harry
        REQUIRE ( mylist.insert ( "Roger",
                                  5 ) == true ); // Tom Ann Paul Dick Roger Harry
        REQUIRE ( mylist.size() == 6 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Tom, Ann, Paul, Dick, Roger, Harry" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Harry, Roger, Dick, Paul, Ann, Tom" );
    }
    SECTION ( "End" )
    {
        CHECK ( mylist.size() == 3 );               // Tom Dick Harry
        REQUIRE ( mylist.insert ( "Ann", 4 ) == true ); // Tom Dick Harry Ann
        REQUIRE ( mylist.insert ( "Paul", 5 ) == true ); // Tom Dick Harry Ann Paul
        REQUIRE ( mylist.insert ( "Roger",
                                  6 ) == true ); // Tom Dick Harry Ann Paul Roger
                                  
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Tom, Dick, Harry, Ann, Paul, Roger" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Roger, Paul, Ann, Harry, Dick, Tom" );
    }
    SECTION ( "Invalid" )
    {
        CHECK ( mylist1.isEmpty() == true ); // Tom Dick Harry
        CHECK ( mylist1.size() == 0 );
        CHECK ( mylist.isEmpty() == false );
        CHECK ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( "Invalid", 0 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( "Invalid", 0 ) == false );
        REQUIRE ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( "Invalid", -1 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( "Invalid", -1 ) == false );
        REQUIRE ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( "Invalid", 2 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( "Invalid", 5 ) == false );
        REQUIRE ( mylist.size() == 3 );
    }
    SECTION ( "DUPLICATES" )
    {
        CHECK ( mylist.size() == 3 );               // Tom Dick Harry
        REQUIRE ( mylist.insert ( "Harry", 4 ) == true );
        REQUIRE ( mylist.insert ( "Dick", 3 ) == true );
        REQUIRE ( mylist.insert ( "Tom", 1 ) == true );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Tom, Tom, Dick, Dick, Harry, Harry" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Harry, Harry, Dick, Dick, Tom, Tom" );
        
    }
}

TEST_CASE ( "Print - Forward" )
{
    unsortedDouble mylistEmpty;
    unsortedDouble mylist;
    ostringstream sout;
    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylist.isEmpty() == false );
    CHECK ( mylistEmpty.size() == 0 );
    CHECK ( mylistEmpty.isEmpty() == true );
    SECTION ( "Print Empty" )
    {
        mylistEmpty.print ( sout );
        REQUIRE ( sout.str() == "" );
    }
    
    SECTION ( "Default - \", \"" )
    {
        mylist.print ( sout );
        REQUIRE ( sout.str() == "Horse, Ox, Cow, Zebra, Monkey, Elephant" );
    }
    SECTION ( "Seperator - \"\"" )
    {
        mylist.print ( sout, true, "" );
        REQUIRE ( sout.str() == "HorseOxCowZebraMonkeyElephant" );
    }
    SECTION ( "Seperator - \":\"" )
    {
        mylist.print ( sout, true, ":" );
        REQUIRE ( sout.str() == "Horse:Ox:Cow:Zebra:Monkey:Elephant" );
    }
    SECTION ( "Seperator - \"-\"" )
    {
        mylist.print ( sout, true, "-" );
        REQUIRE ( sout.str() == "Horse-Ox-Cow-Zebra-Monkey-Elephant" );
    }
    SECTION ( "Seperator - \" - \"" )
    {
        mylist.print ( sout, true, " - " );
        REQUIRE ( sout.str() == "Horse - Ox - Cow - Zebra - Monkey - Elephant" );
    }
}

TEST_CASE ( "Print - Backwards" )
{
    unsortedDouble mylistEmpty;
    unsortedDouble mylist;
    ostringstream sout;
    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylist.isEmpty() == false );
    CHECK ( mylistEmpty.size() == 0 );
    CHECK ( mylistEmpty.isEmpty() == true );
    SECTION ( "Print Empty" )
    {
        mylistEmpty.print ( sout, false );
        REQUIRE ( sout.str() == "" );
    }
    
    SECTION ( "Default - \", \"" )
    {
        mylist.print ( sout, false );
        REQUIRE ( sout.str() == "Elephant, Monkey, Zebra, Cow, Ox, Horse" );
    }
    SECTION ( "Seperator - \"\"" )
    {
        mylist.print ( sout, false, "" );
        REQUIRE ( sout.str() == "ElephantMonkeyZebraCowOxHorse" );
    }
    SECTION ( "Seperator - \":\"" )
    {
        mylist.print ( sout, false, ":" );
        REQUIRE ( sout.str() == "Elephant:Monkey:Zebra:Cow:Ox:Horse" );
    }
    SECTION ( "Seperator - \"-\"" )
    {
        mylist.print ( sout, false, "-" );
        REQUIRE ( sout.str() == "Elephant-Monkey-Zebra-Cow-Ox-Horse" );
    }
    SECTION ( "Seperator - \" - \"" )
    {
        mylist.print ( sout, false, " - " );
        REQUIRE ( sout.str() == "Elephant - Monkey - Zebra - Cow - Ox - Horse" );
    }
}


/*  ************************************************************************ */

TEST_CASE ( "Remove - value" )
{
    unsortedDouble mylistEmpty;
    unsortedDouble mylist;
    ostringstream backw;
    ostringstream forw;
    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Empty" )
    {
        REQUIRE ( mylistEmpty.remove ( "Fred" ) == false );
        REQUIRE ( mylistEmpty.size() == 0 );
        REQUIRE ( mylistEmpty.isEmpty() == true );
        
        mylistEmpty.print ( forw );
        REQUIRE ( forw.str() == "" );
        mylistEmpty.print ( backw, false );
        REQUIRE ( backw.str() == "" );
    }
    
    SECTION ( "Front" ) // Horse Ox Cow Zebra Monkey Elephant
    {
        REQUIRE ( mylist.remove ( "Horse" ) == true );
        REQUIRE ( mylist.remove ( "Ox" ) == true );
        REQUIRE ( mylist.remove ( "Cow" ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Zebra, Monkey, Elephant" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Elephant, Monkey, Zebra" );
    }
    
    SECTION ( "Middle" ) // Horse Ox Cow Zebra Monkey Elephant
    {
        REQUIRE ( mylist.remove ( "Monkey" ) == true );
        REQUIRE ( mylist.remove ( "Ox" ) == true );
        REQUIRE ( mylist.remove ( "Zebra" ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Horse, Cow, Elephant" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Elephant, Cow, Horse" );
    }
    
    SECTION ( "End" ) // Horse Ox Cow Zebra Monkey Elephant
    {
        REQUIRE ( mylist.remove ( "Elephant" ) == true );
        REQUIRE ( mylist.remove ( "Monkey" ) == true );
        REQUIRE ( mylist.remove ( "Zebra" ) == true );
        
        CHECK ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Horse, Ox, Cow" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Cow, Ox, Horse" );
        
    }
    
    
    SECTION ( "Last Item" )
    {
        mylistEmpty.insert ( "Horse" );
        CHECK ( mylistEmpty.size() == 1 );
        
        mylistEmpty.remove ( "Horse" );
        CHECK ( mylistEmpty.isEmpty() == true );
        CHECK ( mylistEmpty.size() == 0 );
        
        mylistEmpty.print ( forw );
        REQUIRE ( forw.str() == "" );
        mylistEmpty.print ( backw, false );
        REQUIRE ( backw.str() == "" );
    }
    
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylistEmpty.remove ( "notinlist" ) == false );
        REQUIRE ( mylist.remove ( "notinlist" ) == false );
    }
}

TEST_CASE ( "Remove - position" )
{
    unsortedDouble mylistEmpty;
    unsortedDouble mylist;
    ostringstream backw;
    ostringstream forw;
    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Empty" )
    {
        REQUIRE ( mylistEmpty.remove ( 1 ) == false );
        REQUIRE ( mylistEmpty.size() == 0 );
        REQUIRE ( mylistEmpty.isEmpty() == true );
        
        mylistEmpty.print ( forw );
        REQUIRE ( forw.str() == "" );
        mylistEmpty.print ( backw, false );
        REQUIRE ( backw.str() == "" );
    }
    
    SECTION ( "Front" ) // Horse Ox Cow Zebra Monkey Elephant
    {
        REQUIRE ( mylist.remove ( 1 ) == true );
        REQUIRE ( mylist.remove ( 1 ) == true );
        REQUIRE ( mylist.remove ( 1 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Zebra, Monkey, Elephant" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Elephant, Monkey, Zebra" );
    }
    
    SECTION ( "Middle" ) // Horse Ox Cow Zebra Monkey Elephant
    {
        REQUIRE ( mylist.remove ( 5 ) == true );
        REQUIRE ( mylist.remove ( 2 ) == true );
        REQUIRE ( mylist.remove ( 3 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Horse, Cow, Elephant" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Elephant, Cow, Horse" );
    }
    
    SECTION ( "End" ) // Horse Ox Cow Zebra Monkey Elephant
    {
        REQUIRE ( mylist.remove ( 6 ) == true );
        REQUIRE ( mylist.remove ( 5 ) == true );
        REQUIRE ( mylist.remove ( 4 ) == true );
        
        CHECK ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "Horse, Ox, Cow" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "Cow, Ox, Horse" );
        
    }
    
    
    SECTION ( "Last Item" )
    {
        mylistEmpty.insert ( "Horse" );
        CHECK ( mylistEmpty.size() == 1 );
        
        mylistEmpty.remove ( 1 );
        CHECK ( mylistEmpty.isEmpty() == true );
        CHECK ( mylistEmpty.size() == 0 );
        
        mylistEmpty.print ( forw );
        REQUIRE ( forw.str() == "" );
        mylistEmpty.print ( backw, false );
        REQUIRE ( backw.str() == "" );
    }
    
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylistEmpty.remove ( -1 ) == false );
        REQUIRE ( mylistEmpty.remove ( 0 ) == false );
        REQUIRE ( mylistEmpty.remove ( 1 ) == false );
        REQUIRE ( mylistEmpty.remove ( 2 ) == false );
        REQUIRE ( mylist.remove ( -1 ) == false );
        REQUIRE ( mylist.remove ( 0 ) == false );
        REQUIRE ( mylist.remove ( 7 ) == false );
        REQUIRE ( mylist.remove ( 8 ) == false );
    }
}

TEST_CASE ( "find" )
{
    unsortedDouble mylist;
    unsortedDouble mylistEmpty;
    
    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Valids" )
    {
        REQUIRE ( mylist.find ( "Horse" ) == true );
        REQUIRE ( mylist.find ( "Zebra" ) == true );
        REQUIRE ( mylist.find ( "Elephant" ) == true );
    }
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylist.find ( "Fish" ) == false );
        REQUIRE ( mylist.find ( "Bird" ) == false );
        REQUIRE ( mylist.find ( "Ant" ) == false );
        REQUIRE ( mylistEmpty.find ( "Fish" ) == false );
        REQUIRE ( mylistEmpty.find ( "Bird" ) == false );
        REQUIRE ( mylistEmpty.find ( "Ant" ) == false );
        
    }
}
TEST_CASE ( "rfind" )
{
    unsortedDouble mylist;
    unsortedDouble mylistEmpty;
    
    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Valids" )
    {
        REQUIRE ( mylist.rfind ( "Horse" ) == true );
        REQUIRE ( mylist.rfind ( "Zebra" ) == true );
        REQUIRE ( mylist.rfind ( "Elephant" ) == true );
    }
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylist.rfind ( "Fish" ) == false );
        REQUIRE ( mylist.rfind ( "Bird" ) == false );
        REQUIRE ( mylist.rfind ( "Ant" ) == false );
        REQUIRE ( mylistEmpty.rfind ( "Fish" ) == false );
        REQUIRE ( mylistEmpty.rfind ( "Bird" ) == false );
        REQUIRE ( mylistEmpty.rfind ( "Ant" ) == false );
        
    }
}


/* ************************************************************************* */

TEST_CASE ( "isEmpty" )
{
    unsortedDouble mylist;
    unsortedDouble mylistEmpty;
    
    REQUIRE ( mylist.isEmpty() == true );
    REQUIRE ( mylistEmpty.isEmpty() == true );
    mylist.insert ( "ox" );
    REQUIRE ( mylist.isEmpty() == false );
    mylist.remove ( "ox" );
    REQUIRE ( mylist.isEmpty() == true );
}

TEST_CASE ( "Size" )
{
    unsortedDouble mylist;
    
    REQUIRE ( mylist.size() == 0 );
    mylist.insert ( "Ox" );             // Ox
    REQUIRE ( mylist.size() == 1 );
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    REQUIRE ( mylist.size() == 2 );
    mylist.insert ( "Zebra", 3 );       // Ox Monkey Zebra
    REQUIRE ( mylist.size() == 3 );
    mylist.insert ( "Elephant", 4 );    // Ox Monkey Zebra Elephant
    REQUIRE ( mylist.size() == 4 );
    mylist.insert ( "Horse", 5 );       // Ox Monkey Zebra Elephant Horse
    REQUIRE ( mylist.size() == 5 );
    mylist.insert ( "Cow", 6 );         // Ox Monkey Zebra Elephant Horse Cow
    REQUIRE ( mylist.size() == 6 );
    
    mylist.remove ( "Ox" );             // Ox
    REQUIRE ( mylist.size() == 5 );
    mylist.remove ( "Monkey" );     // Ox Monkey
    REQUIRE ( mylist.size() == 4 );
    mylist.remove ( "Zebra" );      // Ox Monkey Zebra
    REQUIRE ( mylist.size() == 3 );
    mylist.remove ( "Elephant" );   // Ox Monkey Zebra Elephant
    REQUIRE ( mylist.size() == 2 );
    mylist.remove ( "Horse" );      // Ox Monkey Zebra Elephant Horse
    REQUIRE ( mylist.size() == 1 );
    mylist.remove ( "Cow" );        // Ox Monkey Zebra Elephant Horse Cow
    REQUIRE ( mylist.size() == 0 );
}

TEST_CASE ( "Push Back" )
{
    unsortedDouble mylist;
    ostringstream backw;
    ostringstream forw;
    
    REQUIRE( mylist.push_back ( "Ox" ) == true);         // Ox
    REQUIRE( mylist.push_back ( "Monkey" ) == true);     // Ox Monkey
    REQUIRE( mylist.push_back ( "Zebra" ) == true);      // Ox Monkey Zebra
    REQUIRE( mylist.push_back ( "Elephant" ) == true);   // Ox Monkey Zebra Elephant
    REQUIRE( mylist.push_back ( "Horse" ) == true);      // Ox Monkey Zebra Elephant Horse
    REQUIRE( mylist.push_back ( "Cow" ) == true);        // Ox Monkey Zebra Elephant Horse Cow
    
    REQUIRE ( mylist.size() == 6 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "Ox, Monkey, Zebra, Elephant, Horse, Cow" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "Cow, Horse, Elephant, Zebra, Monkey, Ox" );
}

TEST_CASE ( "Push Front" )
{
    unsortedDouble mylist;
    ostringstream backw;
    ostringstream forw;
    
    REQUIRE( mylist.push_front ( "Ox" ) == true);         // Ox
    REQUIRE( mylist.push_front ( "Monkey" ) == true);     // Monkey Ox
    REQUIRE( mylist.push_front ( "Zebra" ) == true);      // Zebra Monkey Ox
    REQUIRE( mylist.push_front ( "Elephant" ) == true);   // Elephant Zebra Monkey Ox
    REQUIRE( mylist.push_front ( "Horse" ) == true);      // Horse Elephant Zebra Monkey Ox
    REQUIRE( mylist.push_front ( "Cow" ) == true);        // Cow Horse Elephant Zebra Monkey Ox
    
    REQUIRE ( mylist.size() == 6 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "Cow, Horse, Elephant, Zebra, Monkey, Ox" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "Ox, Monkey, Zebra, Elephant, Horse, Cow" );
}




TEST_CASE ( "Pop Back" )
{
    unsortedDouble mylist;
    ostringstream backw;
    ostringstream forw;
    string val;
    
    mylist.insert ( "Ox" );           // Ox
    mylist.insert ( "Monkey",2 );     // Ox Monkey
    mylist.insert ( "Zebra",3 );      // Ox Monkey Zebra
    mylist.insert ( "Elephant",4 );   // Ox Monkey Zebra Elephant
    mylist.insert ( "Horse",5 );      // Ox Monkey Zebra Elephant Horse
    mylist.insert ( "Cow",6 );        // Ox Monkey Zebra Elephant Horse Cow
    REQUIRE ( mylist.size() == 6 );

    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == "Cow");
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == "Horse");
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == "Elephant");

    REQUIRE(mylist.size() == 3 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "Ox, Monkey, Zebra" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "Zebra, Monkey, Ox" );

    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == "Zebra");
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == "Monkey");
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == "Ox");

    forw.str("");
    backw.str("");
    REQUIRE(mylist.size() == 0);
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "" );
}

TEST_CASE ( "Pop Front" )
{
    unsortedDouble mylist;
    ostringstream backw;
    ostringstream forw;
    string val;
    
    mylist.insert ( "Ox" );           // Ox
    mylist.insert ( "Monkey",2 );     // Ox Monkey
    mylist.insert ( "Zebra",3 );      // Ox Monkey Zebra
    mylist.insert ( "Elephant",4 );   // Ox Monkey Zebra Elephant
    mylist.insert ( "Horse",5 );      // Ox Monkey Zebra Elephant Horse
    mylist.insert ( "Cow",6 );        // Ox Monkey Zebra Elephant Horse Cow
    REQUIRE ( mylist.size() == 6 );

    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == "Ox" );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == "Monkey" );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == "Zebra" );

    REQUIRE( mylist.size() == 3 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "Elephant, Horse, Cow");
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "Cow, Horse, Elephant");

    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == "Elephant" );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == "Horse" );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == "Cow" );

    REQUIRE( mylist.size() == 0 );
    forw.str("");
    backw.str("");
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "" );
}
TEST_CASE( "Swap" )
{
    unsortedDouble mylist;
    unsortedDouble mylist2;
    unsortedDouble mylist3;
    unsortedDouble mylist4;
    ostringstream sout1;
    ostringstream sout2;

    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant

    mylist2.insert( "Ann" );            // Ann
    mylist2.insert( "Mary" );           // Mary Ann
    mylist2.insert( "Paul" );           // Paul Mary Ann
    mylist2.insert( "Roger" );          // Roger Paul Mary Ann

    SECTION( "Both Have Content" )
    {
        mylist.swap( mylist2 );

        mylist.print(sout1);
        REQUIRE( sout1.str() == "Roger, Paul, Mary, Ann" );
        mylist2.print(sout2);
        REQUIRE( sout2.str() == "Horse, Ox, Cow, Zebra, Monkey, Elephant");
    }

    SECTION( "Empty list passed non-empty list")
    {
        mylist3.swap(mylist2);
        mylist3.print( sout1 );
        REQUIRE( sout1.str() == "Roger, Paul, Mary, Ann" );
        mylist2.print( sout2 );
        REQUIRE( sout2.str() == "" );

    }
    SECTION( "Non-empty list passed empty list" )
    {
        mylist2.swap(mylist3);
        mylist2.print( sout1 );
        REQUIRE( sout1.str() == "" );
        mylist3.print( sout2 );
        REQUIRE( sout2.str() == "Roger, Paul, Mary, Ann" );
    }

    SECTION( "Two Empty Lists" )
    {
        mylist3.swap( mylist4 );
        REQUIRE( mylist3.isEmpty() == true );
        REQUIRE( mylist4.isEmpty() == true );
    }
}




/* ************************************************************************* */
bool find3length( string s )
{
    if( s.size() == 3 )
        return true;
    return false;
}
bool findValue( string s)
{
    if( s == "Dog" )
        return true;
    return false;
}

TEST_CASE( "Count If")
{
    unsortedDouble mylist;
    unsortedDouble mylist2;

    mylist.push_back( "Ox" );
    mylist.push_back( "Cow" );
    mylist.push_back( "Dog" );
    mylist.push_back( "Dog" );
    mylist.push_back( "Cow" );
    mylist.push_back( "Ox" );
    mylist.push_back( "Cat");
    mylist.push_back( "Dog");

    mylist2.push_back( "Ox" );
    mylist2.push_back( "Horse" );

    REQUIRE( mylist.countIf( find3length ) == 6 );
    REQUIRE( mylist.countIf( findValue ) == 3 );
    REQUIRE( mylist2.countIf( find3length ) == 0 );
    REQUIRE( mylist2.countIf( findValue ) == 0 );

}

TEST_CASE( "Retrieve" )
{
    unsortedDouble mylist;
    unsortedDouble mylistEmpty;
    
    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    mylist.insert ( "Horse", 7 );       // Horse Ox Cow Zebra Monkey Elephant Horse
    mylist.insert ( "Cow", 5 );         // Horse Ox Cow Zebra Cow Monkey Elephant Horse
    mylist.insert ( "Elephant", 2 );    // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse
    mylist.insert ( "Dog", 10 );        // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse Dog

    CHECK( mylist.size() == 10 );
    CHECK( mylistEmpty.size() == 0 );

    // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse Dog
    SECTION("Forward Retrieve")
    {
        REQUIRE( mylist.retrieve("Horse") == 1 );
        REQUIRE( mylist.retrieve("Elephant") == 2 );
        REQUIRE( mylist.retrieve("Cow") == 4);
        REQUIRE( mylist.retrieve( "Dog" ) == 10 );
    }
    // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse Dog
    SECTION("Reverse Retrieve")
    {
        string val;
        mylist.pop_back(val);
        mylist.push_front( "Dog" );
        // Dog Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse

        REQUIRE( mylist.rretrieve( "Horse" ) == 10 );
        REQUIRE( mylist.rretrieve( "Elephant" ) == 9 );
        REQUIRE( mylist.rretrieve( "Cow" ) == 7 );
        REQUIRE( mylist.rretrieve( "Dog" ) == 1 );


    }
    // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse Dog
    SECTION("Retreive Item" )
    {
        string val;
        // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse Dog
        mylist.remove(9);
        mylist.remove(8);
        mylist.remove(6);
        // Horse Elephant Ox Cow Zebra Monkey Dog
        REQUIRE( mylist.size() == 7 );

        REQUIRE( mylist.retrieve( val, 1) == true);
        REQUIRE( val == "Horse" );
        REQUIRE( mylist.retrieve( val, 4) == true);
        REQUIRE( val == "Cow" );
        REQUIRE( mylist.retrieve( val, 7) == true);
        REQUIRE( val == "Dog" );
    }

    SECTION( "Invalids" )
    {
        string val;
        REQUIRE( mylist.retrieve( "Bird" ) == 0);
        REQUIRE( mylist.retrieve( "Fish" ) == 0);
        REQUIRE( mylist.retrieve( "Snake" ) == 0);
        REQUIRE( mylist.rretrieve( "Bird" ) == 0);
        REQUIRE( mylist.rretrieve( "Fish" ) == 0);
        REQUIRE( mylist.rretrieve( "Snake" ) == 0);
        REQUIRE( mylist.retrieve( val, 0 ) == false );
        REQUIRE( mylist.retrieve( val, -1 ) == false );
        REQUIRE( mylist.retrieve( val, 11 ) == false );

    }

}





/* ************************************************************************* */
TEST_CASE( "Copy Constructor" )
{
    unsortedDouble mylist;
    unsortedDouble mylist2;
    unsortedDouble mylist3;
    ostringstream sout1;
    ostringstream sout2;


    mylist.insert ( "Ox" );             // Ox
    mylist.insert ( "Monkey", 2 );      // Ox Monkey
    mylist.insert ( "Zebra", 2 );       // Ox Zebra Monkey
    mylist.insert ( "Elephant", 4 );    // Ox Zebra Monkey Elephant
    mylist.insert ( "Horse", 1 );       // Horse Ox Zebra Monkey Elephant
    mylist.insert ( "Cow", 3 );         // Horse Ox Cow Zebra Monkey Elephant
    mylist.insert ( "Horse", 7 );       // Horse Ox Cow Zebra Monkey Elephant Horse
    mylist.insert ( "Cow", 5 );         // Horse Ox Cow Zebra Cow Monkey Elephant Horse
    mylist.insert ( "Elephant", 2 );    // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse
    mylist.insert ( "Dog", 10 );        // Horse Elephant Ox Cow Zebra Cow Monkey Elephant Horse Dog
    REQUIRE( mylist.size() == 10 );

    REQUIRE( mylist2.isEmpty() == true);
    REQUIRE( mylist2.size() == 0);

    mylist3.insert( "One" );
    REQUIRE( mylist3.size() == 1 );

    SECTION( "Empty Copy")
    {
        unsortedDouble list1(mylist2);

        REQUIRE( list1.isEmpty() == true );
        REQUIRE( list1.size() == 0);
        REQUIRE( mylist2.isEmpty() == true );
        REQUIRE( mylist2.size() == 0);

    }    
    SECTION( "One Item Copy")
    {
        unsortedDouble list1( mylist3 );

        CHECK ( mylist3.size() == 1 );
        CHECK ( list1.size() == 1 );
        CHECK ( mylist3.isEmpty() == false);
        CHECK ( list1.isEmpty() == false );

        list1.print( sout1 );
        mylist3.print( sout2 );

        REQUIRE( sout1.str() == "One" );
        REQUIRE( sout2.str() == "One" );
        REQUIRE( sout1.str() == sout2.str() );
    }
        
    SECTION( "Full Copy")
    {
        unsortedDouble list1( mylist );

        REQUIRE( list1.size() == 10 );
        REQUIRE( mylist.size() == 10 );

        list1.print( sout1 ); 
        mylist.print( sout2 ); 
        REQUIRE( sout1.str() == sout2.str() );

        // make sure it is individual nodes that were truely copied
        mylist.clear();
        sout2.str("");
        list1.print(sout2);
        REQUIRE( sout1.str() == sout2.str() );
    }
}

void copyTest( unsortedDouble valueList, ostream &out )
{
    string item;
    valueList.print(out);
    valueList.pop_back( item );
    valueList.pop_back( item );
    out << " - ";
    valueList.print(out);
}
TEST_CASE("COPY - Function")
{
    unsortedDouble list1;
    unsortedDouble List2;
    ostringstream sout1;
    ostringstream sout2;
    ostringstream sout3;

    list1.insert("One");
    list1.insert("Two", 2);
    list1.insert("Three", 3);
    list1.insert("Four", 4);

    copyTest( list1, sout1 );
    REQUIRE( sout1.str() == "One, Two, Three, Four - One, Two");
    list1.print(sout2);
    REQUIRE( sout2.str() == "One, Two, Three, Four" ); 

}














