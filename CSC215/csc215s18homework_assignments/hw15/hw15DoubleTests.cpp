#include "..\catch.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "unsortedDouble.h"
using namespace std;



TEST_CASE ( "Double - Construtors" )
{
    unsortedDouble<double> mylist;
    ostringstream forw;
    ostringstream back;
    
    REQUIRE ( mylist.isEmpty() == true );
    REQUIRE ( mylist.size() == 0 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( back, false );
    REQUIRE ( back.str() == "" );
}

TEST_CASE ( "Double - Destructors" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylist1;
    ostringstream forw;
    
    forw << fixed << showpoint << setprecision ( 6 );
    mylist.insert ( 42.2 );
    mylist.insert ( 84.4 );
    mylist.insert ( 24.6 );
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
}

TEST_CASE ( "Double - Clear" )
{
    unsortedDouble<double> mylist;
    
    mylist.insert ( 42.2 );
    mylist.insert ( 84.4 );
    mylist.insert ( 24.6 );
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
    mylist.clear();
    REQUIRE ( mylist.size() == 0 );
    REQUIRE ( mylist.isEmpty() );
}

TEST_CASE ( "Double - Insert" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylist1;
    ostringstream forw;
    ostringstream backw;
    forw << fixed << showpoint << setprecision ( 6 );
    backw << fixed << showpoint << setprecision ( 6 );
    
    mylist.insert ( 42.2 );      // 42.2
    mylist.insert ( 24.6, 1 );     // 24.6 42.2
    mylist.insert ( 84.4, 2 );    // 24.6 84.4 42.2
    CHECK ( mylist.size() == 3 );
    CHECK ( !mylist.isEmpty() );
    
    SECTION ( "Empty" )
    {
        CHECK ( mylist1.isEmpty() );
        REQUIRE ( mylist1.insert ( 2048.16 ) == true );
        REQUIRE ( mylist1.size() == 1 );
        REQUIRE ( !mylist1.isEmpty() );
        
        mylist1.print ( forw );
        REQUIRE ( forw.str() == "2048.160000" );
        mylist1.print ( backw, false );
        REQUIRE ( backw.str() == "2048.160000" );
    }
    SECTION ( "Front" )
    {
        mylist1.insert ( 42.2 );                    // 42.2
        REQUIRE ( mylist1.insert ( 84.4, 1 ) == true ); // 84.4 42.2
        REQUIRE ( mylist1.insert ( 24.6, 1 ) == true ); // 24.6 84.4 42.2
        REQUIRE ( mylist1.insert ( 44.88, 1 ) == true ); // 44.88 24.6 84.4 42.2
        REQUIRE ( mylist1.insert ( 21.1024,
                                   1 ) == true ); // 21.1024 44.88 24.6 84.4 42.2
        REQUIRE ( mylist1.insert ( 1024.6,
                                   1 ) == true ); // 1024.6 21.1024 44.88 24.6 84.4 42.2
        CHECK ( mylist1.size() == 6 );
        
        mylist1.print ( forw );
        REQUIRE ( forw.str() ==
                  "1024.600000, 21.102400, 44.880000, 24.600000, 84.400000, 42.200000" );
        mylist1.print ( backw, false );
        REQUIRE ( backw.str() ==
                  "42.200000, 84.400000, 24.600000, 44.880000, 21.102400, 1024.600000" );
    }
    SECTION ( "Middle" )
    {
        CHECK ( mylist.size() == 3 );       // 24.6 84.4 42.2
        REQUIRE ( mylist.insert ( 44.88, 2 ) == true ); // 24.6 44.88 84.4 42.2
        REQUIRE ( mylist.insert ( 21.1024,
                                  3 ) == true ); // 24.6 44.88 21.1024 84.4 42.2
        REQUIRE ( mylist.insert ( 1024.6,
                                  5 ) == true ); // 24.6 44.88 21.1024 84.4 1024.6 42.2
        REQUIRE ( mylist.size() == 6 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() ==
                  "24.600000, 44.880000, 21.102400, 84.400000, 1024.600000, 42.200000" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() ==
                  "42.200000, 1024.600000, 84.400000, 21.102400, 44.880000, 24.600000" );
    }
    SECTION ( "End" )
    {
        CHECK ( mylist.size() == 3 );               // 24.6 84.4 42.2
        REQUIRE ( mylist.insert ( 44.88, 4 ) == true ); // 24.6 84.4 42.2 44.88
        REQUIRE ( mylist.insert ( 21.1024,
                                  5 ) == true ); // 24.6 84.4 42.2 44.88 21.1024
        REQUIRE ( mylist.insert ( 1024.6,
                                  6 ) == true ); // 24.6 84.4 42.2 44.88 21.1024 1024.6
                                  
        mylist.print ( forw );
        REQUIRE ( forw.str() ==
                  "24.600000, 84.400000, 42.200000, 44.880000, 21.102400, 1024.600000" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() ==
                  "1024.600000, 21.102400, 44.880000, 42.200000, 84.400000, 24.600000" );
    }
    SECTION ( "Invalids" )
    {
        CHECK ( mylist1.isEmpty() == true ); // 24.6 84.4 42.2
        CHECK ( mylist1.size() == 0 );
        CHECK ( mylist.isEmpty() == false );
        CHECK ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( -1024.6, 0 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( -1024.6, 0 ) == false );
        REQUIRE ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( -1024.6, -1 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( -1024.6, -1 ) == false );
        REQUIRE ( mylist.size() == 3 );
        
        REQUIRE ( mylist1.insert ( -1024.6, 2 ) == false );
        REQUIRE ( mylist1.size() == 0 );
        REQUIRE ( mylist.insert ( -1024.6, 5 ) == false );
        REQUIRE ( mylist.size() == 3 );
    }
    SECTION ( "DUPLICATES" )
    {
        CHECK ( mylist.size() == 3 );               // 24.6 84.4 42.2
        REQUIRE ( mylist.insert ( 42.2, 4 ) == true );
        REQUIRE ( mylist.insert ( 84.4, 3 ) == true );
        REQUIRE ( mylist.insert ( 24.6, 1 ) == true );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() ==
                  "24.600000, 24.600000, 84.400000, 84.400000, 42.200000, 42.200000" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() ==
                  "42.200000, 42.200000, 84.400000, 84.400000, 24.600000, 24.600000" );
                  
    }
}

TEST_CASE ( "Double - Print - Forward" )
{
    unsortedDouble<double> mylistEmpty;
    unsortedDouble<double> mylist;
    ostringstream sout;
    sout << fixed << showpoint << setprecision ( 6 );
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
                    
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
        REQUIRE ( sout.str() ==
                  "13.655600, 19.493800, 71.184500, 57.987000, 7.340000, 83.659000" );
    }
    SECTION ( "Seperator - \"\"" )
    {
        mylist.print ( sout, true, "" );
        REQUIRE ( sout.str() ==
                  "13.65560019.49380071.18450057.9870007.34000083.659000" );
    }
    SECTION ( "Seperator - \":\"" )
    {
        mylist.print ( sout, true, ":" );
        REQUIRE ( sout.str() ==
                  "13.655600:19.493800:71.184500:57.987000:7.340000:83.659000" );
    }
    SECTION ( "Seperator - \"-\"" )
    {
        mylist.print ( sout, true, "-" );
        REQUIRE ( sout.str() ==
                  "13.655600-19.493800-71.184500-57.987000-7.340000-83.659000" );
    }
    SECTION ( "Seperator - \" - \"" )
    {
        mylist.print ( sout, true, " - " );
        REQUIRE ( sout.str() ==
                  "13.655600 - 19.493800 - 71.184500 - 57.987000 - 7.340000 - 83.659000" );
    }
}

TEST_CASE ( "Double - Print - Backwards" )
{
    unsortedDouble<double> mylistEmpty;
    unsortedDouble<double> mylist;
    ostringstream sout;
    sout << fixed << showpoint << setprecision ( 6 );
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
                    
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
        REQUIRE ( sout.str() ==
                  "83.659000, 7.340000, 57.987000, 71.184500, 19.493800, 13.655600" );
    }
    SECTION ( "Seperator - \"\"" )
    {
        mylist.print ( sout, false, "" );
        REQUIRE ( sout.str() ==
                  "83.6590007.34000057.98700071.18450019.49380013.655600" );
    }
    SECTION ( "Seperator - \":\"" )
    {
        mylist.print ( sout, false, ":" );
        REQUIRE ( sout.str() ==
                  "83.659000:7.340000:57.987000:71.184500:19.493800:13.655600" );
    }
    SECTION ( "Seperator - \"-\"" )
    {
        mylist.print ( sout, false, "-" );
        REQUIRE ( sout.str() ==
                  "83.659000-7.340000-57.987000-71.184500-19.493800-13.655600" );
    }
    SECTION ( "Seperator - \" - \"" )
    {
        mylist.print ( sout, false, " - " );
        REQUIRE ( sout.str() ==
                  "83.659000 - 7.340000 - 57.987000 - 71.184500 - 19.493800 - 13.655600" );
    }
}


/*  ************************************************************************ */

TEST_CASE ( "Double - Remove - value" )
{
    unsortedDouble<double> mylistEmpty;
    unsortedDouble<double> mylist;
    ostringstream backw;
    ostringstream forw;
    
    forw << fixed << showpoint << setprecision ( 6 );
    backw << fixed << showpoint << setprecision ( 6 );
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
                    
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
    
    SECTION ( "Front" ) // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    {
        REQUIRE ( mylist.removeVal ( 13.6556 ) == true );
        REQUIRE ( mylist.removeVal ( 19.4938 ) == true );
        REQUIRE ( mylist.removeVal ( 71.1845 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "57.987000, 7.340000, 83.659000" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83.659000, 7.340000, 57.987000" );
    }
    
    SECTION ( "Middle" ) // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    {
        REQUIRE ( mylist.removeVal ( 7.34 ) == true );
        REQUIRE ( mylist.removeVal ( 19.4938 ) == true );
        REQUIRE ( mylist.removeVal ( 57.987 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13.655600, 71.184500, 83.659000" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83.659000, 71.184500, 13.655600" );
    }
    
    SECTION ( "End" ) // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    {
        REQUIRE ( mylist.removeVal ( 83.659 ) == true );
        REQUIRE ( mylist.removeVal ( 7.34 ) == true );
        REQUIRE ( mylist.removeVal ( 57.987 ) == true );
        
        CHECK ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13.655600, 19.493800, 71.184500" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "71.184500, 19.493800, 13.655600" );
        
    }
    
    
    SECTION ( "Last Item" )
    {
        mylistEmpty.insert ( 13.6556 );
        CHECK ( mylistEmpty.size() == 1 );
        
        mylistEmpty.removeVal ( 13.6556 );
        CHECK ( mylistEmpty.isEmpty() == true );
        CHECK ( mylistEmpty.size() == 0 );
        
        mylistEmpty.print ( forw );
        REQUIRE ( forw.str() == "" );
        mylistEmpty.print ( backw, false );
        REQUIRE ( backw.str() == "" );
    }
    
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylistEmpty.removeVal ( -2048.16 ) == false );
        REQUIRE ( mylist.removeVal ( -2048.16 ) == false );
    }
}

TEST_CASE ( "Double - Remove - position" )
{
    unsortedDouble<double> mylistEmpty;
    unsortedDouble<double> mylist;
    ostringstream backw;
    ostringstream forw;
    forw << fixed << showpoint << setprecision ( 6 );
    backw << fixed << showpoint << setprecision ( 6 );
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
                    
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
    
    SECTION ( "Front" ) // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    {
        REQUIRE ( mylist.remove ( 1 ) == true );
        REQUIRE ( mylist.remove ( 1 ) == true );
        REQUIRE ( mylist.remove ( 1 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "57.987000, 7.340000, 83.659000" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83.659000, 7.340000, 57.987000" );
    }
    
    SECTION ( "Middle" ) // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    {
        REQUIRE ( mylist.remove ( 5 ) == true );
        REQUIRE ( mylist.remove ( 2 ) == true );
        REQUIRE ( mylist.remove ( 3 ) == true );
        
        REQUIRE ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13.655600, 71.184500, 83.659000" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "83.659000, 71.184500, 13.655600" );
    }
    
    SECTION ( "End" ) // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    {
        REQUIRE ( mylist.remove ( 6 ) == true );
        REQUIRE ( mylist.remove ( 5 ) == true );
        REQUIRE ( mylist.remove ( 4 ) == true );
        
        CHECK ( mylist.size() == 3 );
        
        mylist.print ( forw );
        REQUIRE ( forw.str() == "13.655600, 19.493800, 71.184500" );
        mylist.print ( backw, false );
        REQUIRE ( backw.str() == "71.184500, 19.493800, 13.655600" );
        
    }
    
    
    SECTION ( "Last Item" )
    {
        mylistEmpty.insert ( 13.6556 );
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

TEST_CASE ( "Double - find" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylistEmpty;
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
                    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Valids" )
    {
        REQUIRE ( mylist.find ( 13.6556 ) == true );
        REQUIRE ( mylist.find ( 57.987 ) == true );
        REQUIRE ( mylist.find ( 83.659 ) == true );
    }
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylist.find ( 16 ) == false );
        REQUIRE ( mylist.find ( 25 ) == false );
        REQUIRE ( mylist.find ( 121.1024 ) == false );
        REQUIRE ( mylistEmpty.find ( 16 ) == false );
        REQUIRE ( mylistEmpty.find ( 25 ) == false );
        REQUIRE ( mylistEmpty.find ( 121.1024 ) == false );
        
    }
}
TEST_CASE ( "Double - rfind" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylistEmpty;
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
                    
    CHECK ( mylist.size() == 6 );
    CHECK ( mylistEmpty.size() == 0 );
    
    SECTION ( "Valids" )
    {
        REQUIRE ( mylist.rfind ( 13.6556 ) == true );
        REQUIRE ( mylist.rfind ( 57.987 ) == true );
        REQUIRE ( mylist.rfind ( 83.659 ) == true );
    }
    SECTION ( "Invalids" )
    {
        REQUIRE ( mylist.rfind ( -1024.6 ) == false );
        REQUIRE ( mylist.rfind ( -2048.16 ) == false );
        REQUIRE ( mylist.rfind ( -4096.9696 ) == false );
        REQUIRE ( mylistEmpty.rfind ( -1024.6 ) == false );
        REQUIRE ( mylistEmpty.rfind ( -2048.16 ) == false );
        REQUIRE ( mylistEmpty.rfind ( -4096.9696 ) == false );
        
    }
}


/* ************************************************************************* */

TEST_CASE ( "Double - isEmpty" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylistEmpty;
    
    REQUIRE ( mylist.isEmpty() == true );
    REQUIRE ( mylistEmpty.isEmpty() == true );
    mylist.insert ( 42.2 );
    REQUIRE ( mylist.isEmpty() == false );
    mylist.removeVal ( 42.2 );
    REQUIRE ( mylist.isEmpty() == true );
}

TEST_CASE ( "Double - Size" )
{
    unsortedDouble<double> mylist;
    
    REQUIRE ( mylist.size() == 0 );
    mylist.insert ( 19.4938 );             // 19.4938
    REQUIRE ( mylist.size() == 1 );
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    REQUIRE ( mylist.size() == 2 );
    mylist.insert ( 57.987, 3 );       // 19.4938 7.34 57.987
    REQUIRE ( mylist.size() == 3 );
    mylist.insert ( 83.659, 4 );    // 19.4938 7.34 57.987 83.659
    REQUIRE ( mylist.size() == 4 );
    mylist.insert ( 13.6556, 5 );       // 19.4938 7.34 57.987 83.659 13.6556
    REQUIRE ( mylist.size() == 5 );
    mylist.insert ( 71.1845,
                    6 );         // 19.4938 7.34 57.987 83.659 13.6556 71.1845
    REQUIRE ( mylist.size() == 6 );
    
    mylist.removeVal ( 19.4938 );             // 19.4938
    REQUIRE ( mylist.size() == 5 );
    mylist.removeVal ( 7.34 );     // 19.4938 7.34
    REQUIRE ( mylist.size() == 4 );
    mylist.removeVal ( 57.987 );      // 19.4938 7.34 57.987.34
    REQUIRE ( mylist.size() == 3 );
    mylist.removeVal ( 83.659 );   // 19.4938 7.34 57.987 83.659.34
    REQUIRE ( mylist.size() == 2 );
    mylist.removeVal ( 13.6556 );      // 19.4938 7.34 57.987 83.659 13.6556
    REQUIRE ( mylist.size() == 1 );
    mylist.removeVal (
        71.1845 );        // 19.4938 7.34 57.987 83.659 13.6556 71.1845
    REQUIRE ( mylist.size() == 0 );
}

TEST_CASE ( "Double - Push Back" )
{
    unsortedDouble<double> mylist;
    ostringstream backw;
    ostringstream forw;
    forw << fixed << showpoint << setprecision ( 6 );
    backw << fixed << showpoint << setprecision ( 6 );
    
    REQUIRE ( mylist.push_back ( 19.4938 ) == true );       // 19.4938
    REQUIRE ( mylist.push_back ( 7.34 ) == true );   // 19.4938 7.34
    REQUIRE ( mylist.push_back ( 57.987 ) == true );    // 19.4938 7.34 57.987
    REQUIRE ( mylist.push_back ( 83.659 ) ==
              true ); // 19.4938 7.34 57.987 83.659
    REQUIRE ( mylist.push_back ( 13.6556 ) ==
              true );    // 19.4938 7.34 57.987 83.659 13.6556
    REQUIRE ( mylist.push_back ( 71.1845 ) ==
              true );      // 19.4938 7.34 57.987 83.659 13.6556 71.1845
              
    REQUIRE ( mylist.size() == 6 );
    mylist.print ( forw );
    REQUIRE ( forw.str() ==
              "19.493800, 7.340000, 57.987000, 83.659000, 13.655600, 71.184500" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() ==
              "71.184500, 13.655600, 83.659000, 57.987000, 7.340000, 19.493800" );
}

TEST_CASE ( "Double - Push Front" )
{
    unsortedDouble<double> mylist;
    ostringstream backw;
    ostringstream forw;
    forw << fixed << showpoint << setprecision ( 6 );
    backw << fixed << showpoint << setprecision ( 6 );
    
    REQUIRE ( mylist.push_front ( 19.4938 ) == true );       // 19.4938
    REQUIRE ( mylist.push_front ( 7.34 ) == true );   // 7.34 19.4938
    REQUIRE ( mylist.push_front ( 57.987 ) == true );    // 57.987 7.34 19.4938
    REQUIRE ( mylist.push_front ( 83.659 ) ==
              true ); // 83.659 57.987 7.34 19.4938
    REQUIRE ( mylist.push_front ( 13.6556 ) ==
              true );    // 13.6556 83.659 57.987 7.34 19.4938
    REQUIRE ( mylist.push_front ( 71.1845 ) ==
              true );      // 71.1845 13.6556 83.659 57.987 7.34 19.4938
              
    REQUIRE ( mylist.size() == 6 );
    mylist.print ( forw );
    REQUIRE ( forw.str() ==
              "71.184500, 13.655600, 83.659000, 57.987000, 7.340000, 19.493800" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() ==
              "19.493800, 7.340000, 57.987000, 83.659000, 13.655600, 71.184500" );
}




TEST_CASE ( "Double - Pop Back" )
{
    unsortedDouble<double> mylist;
    ostringstream backw;
    ostringstream forw;
    double val;
    
    forw << fixed << showpoint << setprecision ( 6 );
    backw << fixed << showpoint << setprecision ( 6 );
    
    mylist.insert ( 19.4938 );           // 19.4938
    mylist.insert ( 7.34, 2 );    // 19.4938 7.34
    mylist.insert ( 57.987, 3 );    // 19.4938 7.34 57.987
    mylist.insert ( 83.659, 4 );  // 19.4938 7.34 57.987 83.659
    mylist.insert ( 13.6556, 5 );     // 19.4938 7.34 57.987 83.659 13.6556
    mylist.insert ( 71.1845,
                    6 );       // 19.4938 7.34 57.987 83.659 13.6556 71.1845
    REQUIRE ( mylist.size() == 6 );
    
    REQUIRE ( mylist.pop_back ( val ) == true );
    REQUIRE ( val == 71.1845 );
    REQUIRE ( mylist.pop_back ( val ) == true );
    REQUIRE ( val == 13.6556 );
    REQUIRE ( mylist.pop_back ( val ) == true );
    REQUIRE ( val == 83.659 );
    
    REQUIRE ( mylist.size() == 3 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "19.493800, 7.340000, 57.987000" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "57.987000, 7.340000, 19.493800" );
    
    REQUIRE ( mylist.pop_back ( val ) == true );
    REQUIRE ( val == 57.987 );
    REQUIRE ( mylist.pop_back ( val ) == true );
    REQUIRE ( val == 7.34 );
    REQUIRE ( mylist.pop_back ( val ) == true );
    REQUIRE ( val == 19.4938 );
    
    forw.str ( "" );
    backw.str ( "" );
    REQUIRE ( mylist.size() == 0 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "" );
}

TEST_CASE ( "Double - Pop Front" )
{
    unsortedDouble<double> mylist;
    ostringstream backw;
    ostringstream forw;
    double val;
    
    forw << fixed << showpoint << setprecision ( 6 );
    backw << fixed << showpoint << setprecision ( 6 );
    
    mylist.insert ( 19.4938 );           // 19.4938
    mylist.insert ( 7.34, 2 );    // 19.4938 7.34
    mylist.insert ( 57.987, 3 );     // 19.4938 7.34 57.987
    mylist.insert ( 83.659, 4 );  // 19.4938 7.34 57.987 83.659
    mylist.insert ( 13.6556, 5 );     // 19.4938 7.34 57.987 83.659 13.6556
    mylist.insert ( 71.1845,
                    6 );       // 19.4938 7.34 57.987 83.659 13.6556 71.1845
    REQUIRE ( mylist.size() == 6 );
    
    REQUIRE ( mylist.pop_front ( val ) == true );
    REQUIRE ( val == 19.4938 );
    REQUIRE ( mylist.pop_front ( val ) == true );
    REQUIRE ( val == 7.34 );
    REQUIRE ( mylist.pop_front ( val ) == true );
    REQUIRE ( val == 57.987 );
    
    REQUIRE ( mylist.size() == 3 );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "83.659000, 13.655600, 71.184500" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "71.184500, 13.655600, 83.659000" );
    
    REQUIRE ( mylist.pop_front ( val ) == true );
    REQUIRE ( val == 83.659 );
    REQUIRE ( mylist.pop_front ( val ) == true );
    REQUIRE ( val == 13.6556 );
    REQUIRE ( mylist.pop_front ( val ) == true );
    REQUIRE ( val == 71.1845 );
    
    REQUIRE ( mylist.size() == 0 );
    forw.str ( "" );
    backw.str ( "" );
    mylist.print ( forw );
    REQUIRE ( forw.str() == "" );
    mylist.print ( backw, false );
    REQUIRE ( backw.str() == "" );
}
TEST_CASE ( "Double - Swap" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylist2;
    unsortedDouble<double> mylist3;
    unsortedDouble<double> mylist4;
    ostringstream sout1;
    ostringstream sout2;
    sout1 << fixed << showpoint << setprecision ( 6 );
    sout2 << fixed << showpoint << setprecision ( 6 );
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
                    
    mylist2.insert ( 44.88 );           // 44.88
    mylist2.insert ( 2048.16 );          // 2048.16 44.88
    mylist2.insert ( 21.1024 );          // 21.1024 2048.16 44.88
    mylist2.insert ( 1024.6 );         // 1024.6 21.1024 2048.16 44.88
    
    SECTION ( "Both Have Content" )
    {
        mylist.swap ( mylist2 );
        
        mylist.print ( sout1 );
        REQUIRE ( sout1.str() ==
                  "1024.600000, 21.102400, 2048.160000, 44.880000" );
        mylist2.print ( sout2 );
        REQUIRE ( sout2.str() ==
                  "13.655600, 19.493800, 71.184500, 57.987000, 7.340000, 83.659000" );
    }
    
    SECTION ( "Empty list passed non-empty list" )
    {
        mylist3.swap ( mylist2 );
        mylist3.print ( sout1 );
        REQUIRE ( sout1.str() ==
                  "1024.600000, 21.102400, 2048.160000, 44.880000" );
        mylist2.print ( sout2 );
        REQUIRE ( sout2.str() == "" );
        
    }
    SECTION ( "Non-empty list passed empty list" )
    {
        mylist2.swap ( mylist3 );
        mylist2.print ( sout1 );
        REQUIRE ( sout1.str() == "" );
        mylist3.print ( sout2 );
        REQUIRE ( sout2.str() ==
                  "1024.600000, 21.102400, 2048.160000, 44.880000" );
    }
    
    SECTION ( "Two Empty Lists" )
    {
        mylist3.swap ( mylist4 );
        REQUIRE ( mylist3.isEmpty() == true );
        REQUIRE ( mylist4.isEmpty() == true );
    }
}




/* ************************************************************************* */
bool find3length ( double s )
{
    if ( s >= 100.0 )
    {
        return true;
    }
    return false;
}
bool findValue ( double s )
{
    if ( s == 4096.88 )
    {
        return true;
    }
    return false;
}

TEST_CASE ( "Double - Count If" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylist2;
    
    mylist.push_back ( 19.4938 );
    mylist.push_back ( 71.1845 );
    mylist.push_back ( 4096.88 );
    mylist.push_back ( 4096.88 );
    mylist.push_back ( 71.1845 );
    mylist.push_back ( 19.4938 );
    mylist.push_back ( 4000.3 );
    mylist.push_back ( 4096.88 );
    
    mylist2.push_back ( 19.4938 );
    mylist2.push_back ( 13.6556 );
    
    REQUIRE ( mylist.countIf ( find3length ) == 4 );
    REQUIRE ( mylist.countIf ( findValue ) == 3 );
    REQUIRE ( mylist2.countIf ( find3length ) == 0 );
    REQUIRE ( mylist2.countIf ( findValue ) == 0 );
    
}

TEST_CASE ( "Double - Retrieve" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylistEmpty;
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    mylist.insert ( 13.6556,
                    7 );       // 13.6556 19.4938 71.1845 57.987 7.34 83.659 13.6556
    mylist.insert ( 71.1845,
                    5 );         // 13.6556 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556
    mylist.insert ( 83.659,
                    2 );    // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556
    mylist.insert ( 4096,
                    10 );        // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556 4096
                    
    CHECK ( mylist.size() == 10 );
    CHECK ( mylistEmpty.size() == 0 );
    
    // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556 4096
    SECTION ( "Forward Retrieve" )
    {
        REQUIRE ( mylist.retrieve ( 13.6556 ) == 1 );
        REQUIRE ( mylist.retrieve ( 83.659 ) == 2 );
        REQUIRE ( mylist.retrieve ( 71.1845 ) == 4 );
        REQUIRE ( mylist.retrieve ( 4096 ) == 10 );
    }
    // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556 4096
    SECTION ( "Reverse Retrieve" )
    {
        double val;
        mylist.pop_back ( val );
        mylist.push_front ( 4096 );
        // 4096 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556
        
        REQUIRE ( mylist.rretrieve ( 13.6556 ) == 10 );
        REQUIRE ( mylist.rretrieve ( 83.659 ) == 9 );
        REQUIRE ( mylist.rretrieve ( 71.1845 ) == 7 );
        REQUIRE ( mylist.rretrieve ( 4096 ) == 1 );
        
        
    }
    // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556 4096
    SECTION ( "Retreive Item" )
    {
        double val;
        // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556 4096
        mylist.remove ( 9 );
        mylist.remove ( 8 );
        mylist.remove ( 6 );
        // 13.6556 83.659 19.4938 71.1845 57.987 7.34 4096
        REQUIRE ( mylist.size() == 7 );
        
        REQUIRE ( mylist.retrieve ( val, 1 ) == true );
        REQUIRE ( val == 13.6556 );
        REQUIRE ( mylist.retrieve ( val, 4 ) == true );
        REQUIRE ( val == 71.1845 );
        REQUIRE ( mylist.retrieve ( val, 7 ) == true );
        REQUIRE ( val == 4096 );
    }
    
    SECTION ( "Invalids" )
    {
        double val;
        REQUIRE ( mylist.retrieve ( 48 ) == 0 );
        REQUIRE ( mylist.retrieve ( 26 ) == 0 );
        REQUIRE ( mylist.retrieve ( 18 ) == 0 );
        REQUIRE ( mylist.rretrieve ( 48 ) == 0 );
        REQUIRE ( mylist.rretrieve ( 26 ) == 0 );
        REQUIRE ( mylist.rretrieve ( 18 ) == 0 );
        REQUIRE ( mylist.retrieve ( val, 0 ) == false );
        REQUIRE ( mylist.retrieve ( val, -1 ) == false );
        REQUIRE ( mylist.retrieve ( val, 11 ) == false );
        
    }
    
}





/* ************************************************************************* */
TEST_CASE ( "Double - Copy Constructor" )
{
    unsortedDouble<double> mylist;
    unsortedDouble<double> mylist2;
    unsortedDouble<double> mylist3;
    ostringstream sout1;
    ostringstream sout2;
    
    sout1 << fixed << showpoint << setprecision ( 6 );
    sout2 << fixed << showpoint << setprecision ( 6 );
    
    
    mylist.insert ( 19.4938 );             // 19.4938
    mylist.insert ( 7.34, 2 );      // 19.4938 7.34
    mylist.insert ( 57.987, 2 );       // 19.4938 57.987 7.34
    mylist.insert ( 83.659, 4 );    // 19.4938 57.987 7.34 83.659
    mylist.insert ( 13.6556, 1 );       // 13.6556 19.4938 57.987 7.34 83.659
    mylist.insert ( 71.1845,
                    3 );         // 13.6556 19.4938 71.1845 57.987 7.34 83.659
    mylist.insert ( 13.6556,
                    7 );       // 13.6556 19.4938 71.1845 57.987 7.34 83.659 13.6556
    mylist.insert ( 71.1845,
                    5 );         // 13.6556 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556
    mylist.insert ( 83.659,
                    2 );    // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556
    mylist.insert ( 4096,
                    10 );        // 13.6556 83.659 19.4938 71.1845 57.987 71.1845 7.34 83.659 13.6556 4096
    REQUIRE ( mylist.size() == 10 );
    
    REQUIRE ( mylist2.isEmpty() == true );
    REQUIRE ( mylist2.size() == 0 );
    
    mylist3.insert ( 1.2 );
    REQUIRE ( mylist3.size() == 1 );
    
    SECTION ( "Empty Copy" )
    {
        unsortedDouble<double> list1 ( mylist2 );
        
        REQUIRE ( list1.isEmpty() == true );
        REQUIRE ( list1.size() == 0 );
        REQUIRE ( mylist2.isEmpty() == true );
        REQUIRE ( mylist2.size() == 0 );
        
    }
    SECTION ( "One Item Copy" )
    {
        unsortedDouble<double> list1 ( mylist3 );
        
        CHECK ( mylist3.size() == 1 );
        CHECK ( list1.size() == 1 );
        CHECK ( mylist3.isEmpty() == false );
        CHECK ( list1.isEmpty() == false );
        
        list1.print ( sout1 );
        mylist3.print ( sout2 );
        
        REQUIRE ( sout1.str() == "1.200000" );
        REQUIRE ( sout2.str() == "1.200000" );
        REQUIRE ( sout1.str() == sout2.str() );
    }
    
    SECTION ( "Full Copy" )
    {
        unsortedDouble<double> list1 ( mylist );
        
        REQUIRE ( list1.size() == 10 );
        REQUIRE ( mylist.size() == 10 );
        
        list1.print ( sout1 );
        mylist.print ( sout2 );
        REQUIRE ( sout1.str() == sout2.str() );
        
        // make sure it is individual nodes that were truely copied
        mylist.clear();
        sout2.str ( "" );
        list1.print ( sout2 );
        REQUIRE ( sout1.str() == sout2.str() );
    }
}

void copyTest ( unsortedDouble<double> valueList, ostream &out )
{
    double item;
    valueList.print ( out );
    valueList.pop_back ( item );
    valueList.pop_back ( item );
    out << " - ";
    valueList.print ( out );
}
TEST_CASE ( "Double - Copy - Function" )
{
    unsortedDouble<double> list1;
    unsortedDouble<double> List2;
    ostringstream sout1;
    ostringstream sout2;
    ostringstream sout3;
    sout1 << fixed << showpoint << setprecision ( 6 );
    sout2 << fixed << showpoint << setprecision ( 6 );
    sout3 << fixed << showpoint << setprecision ( 6 );
    
    list1.insert ( 1.1 );
    list1.insert ( 2.2, 2 );
    list1.insert ( 3.3, 3 );
    list1.insert ( 4.4, 4 );
    
    copyTest ( list1, sout1 );
    REQUIRE ( sout1.str() ==
              "1.100000, 2.200000, 3.300000, 4.400000 - 1.100000, 2.200000" );
    list1.print ( sout2 );
    REQUIRE ( sout2.str() == "1.100000, 2.200000, 3.300000, 4.400000" );
    
}



TEST_CASE ( "Double - NEW" )
{
    unsortedDouble<double> list1;
    unsortedDouble<double> list2;
    double val1;
    double val2;
    
    SECTION ( "Pop" )
    {
        REQUIRE ( list1.pop_back ( val1 ) == false );
        REQUIRE ( list1.pop_front ( val2 ) == false );
        
        list1.insert ( 42.2 );
        list2.insert ( 42.2 );
        
        
        REQUIRE ( list1.pop_back ( val1 ) == true );
        REQUIRE ( list1.isEmpty() == true );
        REQUIRE ( list1.size() == 0 );
        
        REQUIRE ( list2.pop_front ( val2 ) == true );
        REQUIRE ( list2.isEmpty() == true );
        REQUIRE ( list2.size() == 0 );
    }
    SECTION ( "RETRIEVE" )
    {
        val1 = 1024.6;
        REQUIRE ( list1.retrieve ( val1 ) == 0 );
        REQUIRE ( list1.rretrieve ( val1 ) == 0 );
        
        REQUIRE ( list1.retrieve ( val1, 1 ) == false );
        REQUIRE ( list1.retrieve ( val1, 10 ) == false );
    }
    
}











