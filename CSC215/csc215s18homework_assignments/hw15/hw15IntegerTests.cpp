#include "..\catch.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "unsortedDouble.h"
using namespace std;



TEST_CASE ( "Int - Construtors" )
{
    unsortedDouble<int> mylist;
    ostringstream forw;
    ostringstream back;
    
    REQUIRE ( mylist.isEmpty() == true );
    REQUIRE ( mylist.size() == 0 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( back, false );
    REQUIRE ( back.str() == "" );
}

TEST_CASE ( "Int - Destructors" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylist1;
    ostringstream forw;
    
    mylist.insert ( 42 );
    mylist.insert ( 84 );
    mylist.insert ( 24 );
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
}

TEST_CASE ( "Int - Clear" )
{
    unsortedDouble<int> mylist;
    
    mylist.insert ( 42 );
    mylist.insert ( 84 );
    mylist.insert ( 24 );
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
    mylist.clear();
    REQUIRE ( mylist.size() == 0 );
    REQUIRE ( mylist.isEmpty() );
}

TEST_CASE ( "Int - Insert" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylist1;
    ostringstream forw;
    ostringstream backw;
    
    mylist.insert ( 42 );      // 42
    mylist.insert ( 24, 1 );     // 24 42
    mylist.insert ( 84, 2 );    // 24 84 42
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
    
    SECTION ( "Empty" )
    {
        CHECK ( mylist1.isEmpty() );
        REQUIRE ( mylist1.insert ( 2048 ) == true );
        REQUIRE ( mylist1.size() == 1 );
        REQUIRE ( !mylist1.isEmpty() );
        
        mylist1.print ( forw );
        REQUIRE ( forw.str() == "2048" );
        mylist1.print ( backw, false );
        REQUIRE ( backw.str() == "2048" );
    }
    SECTION ( "Front" )
    {
        mylist1.insert ( 42 );                    // 42
        REQUIRE ( mylist1.insert ( 84, 1 ) == true ); // 84 42
        REQUIRE ( mylist1.insert ( 24, 1 ) == true ); // 24 84 42
        REQUIRE ( mylist1.insert ( 44, 1 ) == true ); // 44 24 84 42
        REQUIRE ( mylist1.insert ( 21,
                                   1 ) == true ); // 21 44 24 84 42
        REQUIRE ( mylist1.insert ( 1024,
                                   1 ) == true ); // 1024 21 44 24 84 42
        CHECK ( mylist1.size() == 6 );
        
        mylist1.print ( forw );
        REQUIRE ( forw.str() == "1024, 21, 44, 24, 84, 42" );
        mylist1.print ( backw, false );
        REQUIRE ( backw.str() == "42, 84, 24, 44, 21, 1024" );
    }
    SECTION ( "Middle" )
    {
        CHECK ( mylist.size() == 3 );       // 24 84 42
        REQUIRE ( mylist.insert ( 44, 2 ) == true ); // 24 44 84 42
        REQUIRE ( mylist.insert ( 21, 3 ) == true ); // 24 44 21 84 42
        REQUIRE ( mylist.insert ( 1024,
                                  5 ) == true ); // 24 44 21 84 1024 42
        REQUIRE ( mylist.size() == 6 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "24, 44, 21, 84, 1024, 42" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "42, 1024, 84, 21, 44, 24" );
    }
    SECTION ( "End" )
    {
        CHECK ( mylist.size() == 3 );               // 24 84 42
        REQUIRE ( mylist.insert ( 44, 4 ) == true ); // 24 84 42 44
        REQUIRE ( mylist.insert ( 21, 5 ) == true ); // 24 84 42 44 21
        REQUIRE ( mylist.insert ( 1024,
                                  6 ) == true ); // 24 84 42 44 21 1024
                                  
        mylist.print ( forw );
        REQUIRE ( forw.str() == "24, 84, 42, 44, 21, 1024" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "1024, 21, 44, 42, 84, 24" );
    }
    SECTION ( "Invalids" )
    {
        CHECK ( mylist1.isEmpty() == true ); // 24 84 42
        CHECK ( mylist1.size() == 0 );
        CHECK ( mylist.isEmpty() == false );
        CHECK ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( -1024, 0 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( -1024, 0 ) == false );
        REQUIRE ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( -1024, -1 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( -1024, -1 ) == false );
        REQUIRE ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( -1024, 2 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( -1024, 5 ) == false );
        REQUIRE ( mylist.size() == 3 );
    }
    SECTION ( "DUPLICATES" )
    {
        CHECK ( mylist.size() == 3 );               // 24 84 42
        REQUIRE ( mylist.insert ( 42, 4 ) == true );
        REQUIRE ( mylist.insert ( 84, 3 ) == true );
        REQUIRE ( mylist.insert ( 24, 1 ) == true );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "24, 24, 84, 84, 42, 42" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "42, 42, 84, 84, 24, 24" );
        
    }
}

TEST_CASE ( "Int - Print - Forward" )
{
    unsortedDouble<int> mylistEmpty;
    unsortedDouble<int> mylist;
    ostringstream sout;
    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    
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
        REQUIRE ( sout.str() == "13, 19, 17, 57, 7, 83" );
    }
    SECTION ( "Seperator - \"\"" )
    {
        mylist.print ( sout, true, "" );
        REQUIRE ( sout.str() == "13191757783" );
    }
    SECTION ( "Seperator - \":\"" )
    {
        mylist.print ( sout, true, ":" );
        REQUIRE ( sout.str() == "13:19:17:57:7:83" );
    }
    SECTION ( "Seperator - \"-\"" )
    {
        mylist.print ( sout, true, "-" );
        REQUIRE ( sout.str() == "13-19-17-57-7-83" );
    }
    SECTION ( "Seperator - \" - \"" )
    {
        mylist.print ( sout, true, " - " );
        REQUIRE ( sout.str() == "13 - 19 - 17 - 57 - 7 - 83" );
    }
}

TEST_CASE ( "Int - Print - Backwards" )
{
    unsortedDouble<int> mylistEmpty;
    unsortedDouble<int> mylist;
    ostringstream sout;
    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    
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
        REQUIRE ( sout.str() == "83, 7, 57, 17, 19, 13" );
    }
    SECTION ( "Seperator - \"\"" )
    {
        mylist.print ( sout, false, "" );
        REQUIRE ( sout.str() == "83757171913" );
    }
    SECTION ( "Seperator - \":\"" )
    {
        mylist.print ( sout, false, ":" );
        REQUIRE ( sout.str() == "83:7:57:17:19:13" );
    }
    SECTION ( "Seperator - \"-\"" )
    {
        mylist.print ( sout, false, "-" );
        REQUIRE ( sout.str() == "83-7-57-17-19-13" );
    }
    SECTION ( "Seperator - \" - \"" )
    {
        mylist.print ( sout, false, " - " );
        REQUIRE ( sout.str() == "83 - 7 - 57 - 17 - 19 - 13" );
    }
}


/*  ************************************************************************ */

TEST_CASE ( "Int - Remove - value" )
{
    unsortedDouble<int> mylistEmpty;
    unsortedDouble<int> mylist;
    ostringstream backw;
    ostringstream forw;
    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Empty" )
    {
        REQUIRE ( mylistEmpty.removeVal ( 43 ) == false );
        REQUIRE ( mylistEmpty.size() == 0 );
        REQUIRE ( mylistEmpty.isEmpty() == true );
        
        mylistEmpty.print ( forw );
        REQUIRE ( forw.str() == "" );
        mylistEmpty.print ( backw, false );
        REQUIRE ( backw.str() == "" );
    }
    
    SECTION ( "Front" ) // 13 19 17 57 7 83
    {
        REQUIRE ( mylist.removeVal ( 13 ) == true );
        REQUIRE ( mylist.removeVal ( 19 ) == true );
        REQUIRE ( mylist.removeVal ( 17 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "57, 7, 83" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83, 7, 57" );
    }
    
    SECTION ( "Middle" ) // 13 19 17 57 7 83
    {
        REQUIRE ( mylist.removeVal ( 7 ) == true );
        REQUIRE ( mylist.removeVal ( 19 ) == true );
        REQUIRE ( mylist.removeVal ( 57 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13, 17, 83" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83, 17, 13" );
    }
    
    SECTION ( "End" ) // 13 19 17 57 7 83
    {
        REQUIRE ( mylist.removeVal ( 83 ) == true );
        REQUIRE ( mylist.removeVal ( 7 ) == true );
        REQUIRE ( mylist.removeVal ( 57 ) == true );
        
        CHECK ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13, 19, 17" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "17, 19, 13" );
        
    }
    
    
    SECTION ( "Last Item" )
    {
        mylistEmpty.insert ( 13 );
        CHECK ( mylistEmpty.size() == 1 );
        
        mylistEmpty.removeVal ( 13 );
        CHECK ( mylistEmpty.isEmpty() == true );
        CHECK ( mylistEmpty.size() == 0 );
        
        mylistEmpty.print ( forw );
        REQUIRE ( forw.str() == "" );
        mylistEmpty.print ( backw, false );
        REQUIRE ( backw.str() == "" );
    }
    
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylistEmpty.removeVal ( -2048 ) == false );
        REQUIRE ( mylist.removeVal ( -2048 ) == false );
    }
}

TEST_CASE ( "Int - Remove - position" )
{
    unsortedDouble<int> mylistEmpty;
    unsortedDouble<int> mylist;
    ostringstream backw;
    ostringstream forw;
    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    
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
    
    SECTION ( "Front" ) // 13 19 17 57 7 83
    {
        REQUIRE ( mylist.remove ( 1 ) == true );
        REQUIRE ( mylist.remove ( 1 ) == true );
        REQUIRE ( mylist.remove ( 1 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "57, 7, 83" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83, 7, 57" );
    }
    
    SECTION ( "Middle" ) // 13 19 17 57 7 83
    {
        REQUIRE ( mylist.remove ( 5 ) == true );
        REQUIRE ( mylist.remove ( 2 ) == true );
        REQUIRE ( mylist.remove ( 3 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13, 17, 83" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83, 17, 13" );
    }
    
    SECTION ( "End" ) // 13 19 17 57 7 83
    {
        REQUIRE ( mylist.remove ( 6 ) == true );
        REQUIRE ( mylist.remove ( 5 ) == true );
        REQUIRE ( mylist.remove ( 4 ) == true );
        
        CHECK ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13, 19, 17" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "17, 19, 13" );
        
    }
    
    
    SECTION ( "Last Item" )
    {
        mylistEmpty.insert ( 13 );
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

TEST_CASE ( "Int - find" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylistEmpty;
    
    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Valids" )
    {
        REQUIRE ( mylist.find ( 13 ) == true );
        REQUIRE ( mylist.find ( 57 ) == true );
        REQUIRE ( mylist.find ( 83 ) == true );
    }
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylist.find ( 16 ) == false );
        REQUIRE ( mylist.find ( 25 ) == false );
        REQUIRE ( mylist.find ( 121 ) == false );
        REQUIRE ( mylistEmpty.find ( 16 ) == false );
        REQUIRE ( mylistEmpty.find ( 25 ) == false );
        REQUIRE ( mylistEmpty.find ( 121 ) == false );
        
    }
}
TEST_CASE ( "Int - rfind" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylistEmpty;
    
    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Valids" )
    {
        REQUIRE ( mylist.rfind ( 13 ) == true );
        REQUIRE ( mylist.rfind ( 57 ) == true );
        REQUIRE ( mylist.rfind ( 83 ) == true );
    }
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylist.rfind ( -1024 ) == false );
        REQUIRE ( mylist.rfind ( -2048 ) == false );
        REQUIRE ( mylist.rfind ( -4096 ) == false );
        REQUIRE ( mylistEmpty.rfind ( -1024 ) == false );
        REQUIRE ( mylistEmpty.rfind ( -2048 ) == false );
        REQUIRE ( mylistEmpty.rfind ( -4096 ) == false );
        
    }
}


/* ************************************************************************* */

TEST_CASE ( "Int - isEmpty" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylistEmpty;
    
    REQUIRE ( mylist.isEmpty() == true );
    REQUIRE ( mylistEmpty.isEmpty() == true );
    mylist.insert ( 42 );
    REQUIRE ( mylist.isEmpty() == false );
    mylist.removeVal ( 42 );
    REQUIRE ( mylist.isEmpty() == true );
}

TEST_CASE ( "Int - Size" )
{
    unsortedDouble<int> mylist;
    
    REQUIRE ( mylist.size() == 0 );
    mylist.insert ( 19 );             // 19
    REQUIRE ( mylist.size() == 1 );
    mylist.insert ( 7, 2 );      // 19 7
    REQUIRE ( mylist.size() == 2 );
    mylist.insert ( 57, 3 );       // 19 7 57
    REQUIRE ( mylist.size() == 3 );
    mylist.insert ( 83, 4 );    // 19 7 57 83
    REQUIRE ( mylist.size() == 4 );
    mylist.insert ( 13, 5 );       // 19 7 57 83 13
    REQUIRE ( mylist.size() == 5 );
    mylist.insert ( 17, 6 );         // 19 7 57 83 13 17
    REQUIRE ( mylist.size() == 6 );
    
    mylist.removeVal ( 19 );             // 19
    REQUIRE ( mylist.size() == 5 );
    mylist.removeVal ( 7 );     // 19 7
    REQUIRE ( mylist.size() == 4 );
    mylist.removeVal ( 57 );      // 19 7 57
    REQUIRE ( mylist.size() == 3 );
    mylist.removeVal ( 83 );   // 19 7 57 83
    REQUIRE ( mylist.size() == 2 );
    mylist.removeVal ( 13 );      // 19 7 57 83 13
    REQUIRE ( mylist.size() == 1 );
    mylist.removeVal ( 17 );        // 19 7 57 83 13 17
    REQUIRE ( mylist.size() == 0 );
}

TEST_CASE ( "Int - Push Back" )
{
    unsortedDouble<int> mylist;
    ostringstream backw;
    ostringstream forw;
    
    REQUIRE( mylist.push_back ( 19 ) == true);         // 19
    REQUIRE( mylist.push_back ( 7 ) == true);     // 19 7
    REQUIRE( mylist.push_back ( 57 ) == true);      // 19 7 57
    REQUIRE( mylist.push_back ( 83 ) == true);   // 19 7 57 83
    REQUIRE( mylist.push_back ( 13 ) == true);      // 19 7 57 83 13
    REQUIRE( mylist.push_back ( 17 ) == true);        // 19 7 57 83 13 17
    
    REQUIRE ( mylist.size() == 6 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "19, 7, 57, 83, 13, 17" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "17, 13, 83, 57, 7, 19" );
}

TEST_CASE ( "Int - Push Front" )
{
    unsortedDouble<int> mylist;
    ostringstream backw;
    ostringstream forw;
    
    REQUIRE( mylist.push_front ( 19 ) == true);         // 19
    REQUIRE( mylist.push_front ( 7 ) == true);     // 7 19
    REQUIRE( mylist.push_front ( 57 ) == true);      // 57 7 19
    REQUIRE( mylist.push_front ( 83 ) == true);   // 83 57 7 19
    REQUIRE( mylist.push_front ( 13 ) == true);      // 13 83 57 7 19
    REQUIRE( mylist.push_front ( 17 ) == true);        // 17 13 83 57 7 19
    
    REQUIRE ( mylist.size() == 6 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "17, 13, 83, 57, 7, 19" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "19, 7, 57, 83, 13, 17" );
}




TEST_CASE ( "Int - Pop Back" )
{
    unsortedDouble<int> mylist;
    ostringstream backw;
    ostringstream forw;
    int val;
    
    mylist.insert ( 19 );           // 19
    mylist.insert ( 7,2 );     // 19 7
    mylist.insert ( 57,3 );      // 19 7 57
    mylist.insert ( 83,4 );   // 19 7 57 83
    mylist.insert ( 13,5 );      // 19 7 57 83 13
    mylist.insert ( 17,6 );        // 19 7 57 83 13 17
    REQUIRE ( mylist.size() == 6 );

    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == 17);
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == 13);
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == 83);

    REQUIRE(mylist.size() == 3 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "19, 7, 57" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "57, 7, 19" );

    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == 57);
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == 7);
    REQUIRE(mylist.pop_back(val) == true );
    REQUIRE( val == 19);

    forw.str("");
    backw.str("");
    REQUIRE(mylist.size() == 0);
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "" );
}

TEST_CASE ( "Int - Pop Front" )
{
    unsortedDouble<int> mylist;
    ostringstream backw;
    ostringstream forw;
    int val;
    
    mylist.insert ( 19 );           // 19
    mylist.insert ( 7,2 );     // 19 7
    mylist.insert ( 57,3 );      // 19 7 57
    mylist.insert ( 83,4 );   // 19 7 57 83
    mylist.insert ( 13,5 );      // 19 7 57 83 13
    mylist.insert ( 17,6 );        // 19 7 57 83 13 17
    REQUIRE ( mylist.size() == 6 );

    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == 19 );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == 7 );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == 57 );

    REQUIRE( mylist.size() == 3 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "83, 13, 17");
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "17, 13, 83");

    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == 83 );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == 13 );
    REQUIRE( mylist.pop_front(val) == true);
    REQUIRE( val == 17 );

    REQUIRE( mylist.size() == 0 );
    forw.str("");
    backw.str("");
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "" );
}
TEST_CASE( "Int - Swap" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylist2;
    unsortedDouble<int> mylist3;
    unsortedDouble<int> mylist4;
    ostringstream sout1;
    ostringstream sout2;

    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83

    mylist2.insert( 44 );            // 44
    mylist2.insert( 2048 );           // Mary 44
    mylist2.insert( 21 );           // 21 Mary 44
    mylist2.insert( 1024 );          // 1024 21 Mary 44

    SECTION( "Both Have Content" )
    {
        mylist.swap( mylist2 );

        mylist.print(sout1);
        REQUIRE( sout1.str() == "1024, 21, 2048, 44" );
        mylist2.print(sout2);
        REQUIRE( sout2.str() == "13, 19, 17, 57, 7, 83");
    }

    SECTION( "Empty list passed non-empty list")
    {
        mylist3.swap(mylist2);
        mylist3.print( sout1 );
        REQUIRE( sout1.str() == "1024, 21, 2048, 44" );
        mylist2.print( sout2 );
        REQUIRE( sout2.str() == "" );

    }
    SECTION( "Non-empty list passed empty list" )
    {
        mylist2.swap(mylist3);
        mylist2.print( sout1 );
        REQUIRE( sout1.str() == "" );
        mylist3.print( sout2 );
        REQUIRE( sout2.str() == "1024, 21, 2048, 44" );
    }

    SECTION( "Two Empty Lists" )
    {
        mylist3.swap( mylist4 );
        REQUIRE( mylist3.isEmpty() == true );
        REQUIRE( mylist4.isEmpty() == true );
    }
}




/* ************************************************************************* */
bool find3length( int s )
{
    if( s >= 50 )
        return true;
    return false;
}
bool findValue( int s)
{
    if( s == 4096 )
        return true;
    return false;
}

TEST_CASE( "Int - Count If")
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylist2;

    mylist.push_back( 19 );
    mylist.push_back( 17 );
    mylist.push_back( 4096 );
    mylist.push_back( 4096 );
    mylist.push_back( 17 );
    mylist.push_back( 19 );
    mylist.push_back( 4000);
    mylist.push_back( 4096);

    mylist2.push_back( 19 );
    mylist2.push_back( 13 );

    REQUIRE( mylist.countIf( find3length ) == 4 );
    REQUIRE( mylist.countIf( findValue ) == 3 );
    REQUIRE( mylist2.countIf( find3length ) == 0 );
    REQUIRE( mylist2.countIf( findValue ) == 0 );

}

TEST_CASE( "Int - Retrieve" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylistEmpty;
    
    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    mylist.insert ( 13, 7 );       // 13 19 17 57 7 83 13
    mylist.insert ( 17, 5 );         // 13 19 17 57 17 7 83 13
    mylist.insert ( 83, 2 );    // 13 83 19 17 57 17 7 83 13
    mylist.insert ( 4096, 10 );        // 13 83 19 17 57 17 7 83 13 4096

    CHECK( mylist.size() == 10 );
    CHECK( mylistEmpty.size() == 0 );

    // 13 83 19 17 57 17 7 83 13 4096
    SECTION("Forward Retrieve")
    {
        REQUIRE( mylist.retrieve(13) == 1 );
        REQUIRE( mylist.retrieve(83) == 2 );
        REQUIRE( mylist.retrieve(17) == 4);
        REQUIRE( mylist.retrieve( 4096 ) == 10 );
    }
    // 13 83 19 17 57 17 7 83 13 4096
    SECTION("Reverse Retrieve")
    {
        int val;
        mylist.pop_back(val);
        mylist.push_front( 4096 );
        // 4096 13 83 19 17 57 17 7 83 13

        REQUIRE( mylist.rretrieve( 13 ) == 10 );
        REQUIRE( mylist.rretrieve( 83 ) == 9 );
        REQUIRE( mylist.rretrieve( 17 ) == 7 );
        REQUIRE( mylist.rretrieve( 4096 ) == 1 );


    }
    // 13 83 19 17 57 17 7 83 13 4096
    SECTION("Retreive Item" )
    {
        int val;
        // 13 83 19 17 57 17 7 83 13 4096
        mylist.remove(9);
        mylist.remove(8);
        mylist.remove(6);
        // 13 83 19 17 57 7 4096
        REQUIRE( mylist.size() == 7 );

        REQUIRE( mylist.retrieve( val, 1) == true);
        REQUIRE( val == 13 );
        REQUIRE( mylist.retrieve( val, 4) == true);
        REQUIRE( val == 17 );
        REQUIRE( mylist.retrieve( val, 7) == true);
        REQUIRE( val == 4096 );
    }

    SECTION( "Invalids" )
    {
        int val;
        REQUIRE( mylist.retrieve( 48 ) == 0);
        REQUIRE( mylist.retrieve( 26 ) == 0);
        REQUIRE( mylist.retrieve( 18 ) == 0);
        REQUIRE( mylist.rretrieve( 48 ) == 0);
        REQUIRE( mylist.rretrieve( 26 ) == 0);
        REQUIRE( mylist.rretrieve( 18 ) == 0);
        REQUIRE( mylist.retrieve( val, 0 ) == false );
        REQUIRE( mylist.retrieve( val, -1 ) == false );
        REQUIRE( mylist.retrieve( val, 11 ) == false );

    }

}





/* ************************************************************************* */
TEST_CASE( "Int - Copy Constructor" )
{
    unsortedDouble<int> mylist;
    unsortedDouble<int> mylist2;
    unsortedDouble<int> mylist3;
    ostringstream sout1;
    ostringstream sout2;


    mylist.insert ( 19 );             // 19
    mylist.insert ( 7, 2 );      // 19 7
    mylist.insert ( 57, 2 );       // 19 57 7
    mylist.insert ( 83, 4 );    // 19 57 7 83
    mylist.insert ( 13, 1 );       // 13 19 57 7 83
    mylist.insert ( 17, 3 );         // 13 19 17 57 7 83
    mylist.insert ( 13, 7 );       // 13 19 17 57 7 83 13
    mylist.insert ( 17, 5 );         // 13 19 17 57 17 7 83 13
    mylist.insert ( 83, 2 );    // 13 83 19 17 57 17 7 83 13
    mylist.insert ( 4096, 10 );        // 13 83 19 17 57 17 7 83 13 4096
    REQUIRE( mylist.size() == 10 );

    REQUIRE( mylist2.isEmpty() == true);
    REQUIRE( mylist2.size() == 0);

    mylist3.insert( 1 );
    REQUIRE( mylist3.size() == 1 );

    SECTION( "Empty Copy")
    {
        unsortedDouble<int> list1(mylist2);

        REQUIRE( list1.isEmpty() == true );
        REQUIRE( list1.size() == 0);
        REQUIRE( mylist2.isEmpty() == true );
        REQUIRE( mylist2.size() == 0);

    }    
    SECTION( "One Item Copy")
    {
        unsortedDouble<int> list1( mylist3 );

        CHECK ( mylist3.size() == 1 );
        CHECK ( list1.size() == 1 );
        CHECK ( mylist3.isEmpty() == false);
        CHECK ( list1.isEmpty() == false );

        list1.print( sout1 );
        mylist3.print( sout2 );

        REQUIRE( sout1.str() == "1" );
        REQUIRE( sout2.str() == "1" );
        REQUIRE( sout1.str() == sout2.str() );
    }
        
    SECTION( "Full Copy")
    {
        unsortedDouble<int> list1( mylist );

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

void copyTest( unsortedDouble<int> valueList, ostream &out )
{
    int item;
    valueList.print(out);
    valueList.pop_back( item );
    valueList.pop_back( item );
    out << " - ";
    valueList.print(out);
}
TEST_CASE("Int - Copy - Function")
{
    unsortedDouble<int> list1;
    unsortedDouble<int> List2;
    ostringstream sout1;
    ostringstream sout2;
    ostringstream sout3;

    list1.insert(1);
    list1.insert(2, 2);
    list1.insert(3, 3);
    list1.insert(4, 4);

    copyTest( list1, sout1 );
    REQUIRE( sout1.str() == "1, 2, 3, 4 - 1, 2");
    list1.print(sout2);
    REQUIRE( sout2.str() == "1, 2, 3, 4" ); 

}



TEST_CASE("Int - NEW")
{
    unsortedDouble<int> list1;
    unsortedDouble<int> list2;
    int val1;
    int val2;

    SECTION("Pop")
    {
        REQUIRE( list1.pop_back( val1 ) == false );
        REQUIRE( list1.pop_front( val2 ) == false );

        list1.insert(42);
        list2.insert(42);

        
        REQUIRE( list1.pop_back(val1) == true );
        REQUIRE( list1.isEmpty() == true );
        REQUIRE( list1.size() == 0 );

        REQUIRE( list2.pop_front(val2) == true );
        REQUIRE( list2.isEmpty() == true );
        REQUIRE( list2.size() == 0 );
    }
    SECTION("RETRIEVE")
    {
        val1 = 1024;
        REQUIRE(list1.retrieve( val1 ) == 0);
        REQUIRE(list1.rretrieve( val1 ) == 0);

        REQUIRE(list1.retrieve(val1,1) == false);
        REQUIRE(list1.retrieve(val1,10) == false );
    }
}











