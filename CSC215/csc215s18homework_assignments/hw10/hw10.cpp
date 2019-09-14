#define CATCH_CONFIG_MAIN
#include "..\catch.hpp"
#include <iostream>
#include <string>
#include <sstream>

#include "unsortedDouble.h"

using namespace std;


TEST_CASE ( "Constructors" )
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
