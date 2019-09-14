#define CATCH_CONFIG_MAIN
#include <string>
#include "stringplus.h"
#include "..\catch.hpp"
using std::string;


/********************************************************************
 * TrimString test Cases for Front
 *******************************************************************/
TEST_CASE( "trimString-front 1: No Spaces on either side\n"
           "Given string \"This is my string\"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'F'\n")
{
    string str = "This is my string";
    string ans = "This is my string";
    char method = 'F';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-front 2: Spaces at the front to be removed\n"
           "Given string \"   This is my string\"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'F'\n")
{
    string str = "   This is my string";
    string ans = "This is my string";
    char method = 'F';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-front 3: All types of white Spaces at the front\n"
           "Given string \" \\t\\n\\v\\f\\r This is my string\"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'F'\n")
{
    string str = " \t\n\v\f\r This is my string";
    string ans = "This is my string";
    char method = 'F';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-front 4: All types of white Spaces in front and end"
           " remove from front only\n"
           "Given string \" \\t\\n\\v\\f\\r My string \\t\\n\\v\\f\\r \"\n"
           "Expect string \"My string \\t\\n\\v\\f\\r \"\n"
           "With Method 'f'\n")
{
    string str = " \t\n\v\f\r My string \t\n\v\f\r ";
    string ans = "My string \t\n\v\f\r ";
    char method = 'f';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-front 5: An empty string\n"
           "Given string \"\"\n"
           "Expect string \"\"\n"
           "With Method 'f'\n")
{
    string str = "";
    string ans = "";
    char method = 'f';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-front 6: String that becomes empty\n"
           "Given string \"  \\t\\t\\n\\v\\f\\r  \"\n"
           "Expect string \"\"\n"
           "With Method 'f'\n")
{
    string str = "  \t\t\n\v\f\r  ";
    string ans = "";
    char method = 'f';

    trimString( str, method );
    REQUIRE( str == ans );
}






/********************************************************************
 * TrimString test Cases for Back 
 *******************************************************************/
TEST_CASE( "trimString-end 1: No Spaces on either side\n"
           "Given string \"This is my string\"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'E'\n")
{
    string str = "This is my string";
    string ans = "This is my string";
    char method = 'E';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-end 2: Spaces at the end to be removed\n"
           "Given string \"This is my string   \"\n"
           "Expect string \"This is my string   \"\n"
           "With Method 'e'\n")
{
    string str = "This is my string   ";
    string ans = "This is my string";
    char method = 'e';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-end 3: All types of white Spaces at the end\n"
           "Given string \"This is my String \\t\\n\\v\\f\\r \"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'E'\n")
{
    string str = "This is my string \t\n\v\f\r ";
    string ans = "This is my string";
    char method = 'E';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-end 4: All types of white Spaces in front and end"
           " remove from end only\n"
           "Given string \" \\t\\n\\v\\f\\r My string \\t\\n\\v\\f\\r \"\n"
           "Expect string \"My string \\t\\n\\v\\f\\r \"\n"
           "With Method 'E'\n")
{
    string str = " \t\n\v\f\r My string \t\n\v\f\r ";
    string ans = " \t\n\v\f\r My string";
    char method = 'E';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-end 5: An empty string\n"
           "Given string \"\"\n"
           "Expect string \"\"\n"
           "With Method 'e'\n")
{
    string str = "";
    string ans = "";
    char method = 'e';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-end 6: String that becomes empty\n"
           "Given string \"  \\t\\t\\n\\v\\f\\r  \"\n"
           "Expect string \"\"\n"
           "With Method 'E'\n")
{
    string str = "  \t\t\n\v\f\r  ";
    string ans = "";
    char method = 'E';

    trimString( str, method );
    REQUIRE( str == ans );
}



/********************************************************************
 * TrimString test Cases for Both 
 *******************************************************************/
TEST_CASE( "trimString-both 1: No Spaces on either side\n"
           "Given string \"This is my string\"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'B'\n")
{
    string str = "This is my string";
    string ans = "This is my string";
    char method = 'B';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-both 2: Spaces at the end to be removed\n"
           "Given string \"This is my string   \"\n"
           "Expect string \"This is my string   \"\n"
           "With Method 'b'\n")
{
    string str = "This is my string   ";
    string ans = "This is my string";
    char method = 'b';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-both 3: Spaces at the front to be removed\n"
           "Given string \"   This is my string\"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'b'\n")
{
    string str = "   This is my string";
    string ans = "This is my string";
    char method = 'b';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-both 4: Spaces at the front to be removed\n"
           "Given string \"   This is my string   \"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'b'\n")
{
    string str = "   This is my string   ";
    string ans = "This is my string";
    char method = 'b';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-both 5: All types of white Spaces at the front\n"
           "Given string \" \\t\\n\\v\\f\\r This is my String\"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'B'\n")
{
    string str = " \t\n\v\f\r This is my string";
    string ans = "This is my string";
    char method = 'B';

    trimString( str, method );
    REQUIRE( str == ans );
}

TEST_CASE( "trimString-both 6: All types of white Spaces at the end\n"
           "Given string \"This is my String \\t\\n\\v\\f\\r \"\n"
           "Expect string \"This is my string\"\n"
           "With Method 'B'\n")
{
    string str = "This is my string \t\n\v\f\r ";
    string ans = "This is my string";
    char method = 'B';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-both 7: All types of white Spaces in front and end"
           " remove from end only\n"
           "Given string \" \\t\\n\\v\\f\\r My string \\t\\n\\v\\f\\r \"\n"
           "Expect string \"My string \\t\\n\\v\\f\\r \"\n"
           "With Method 'B'\n")
{
    string str = " \t\n\v\f\r My string \t\n\v\f\r ";
    string ans = "My string";
    char method = 'B';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-both 8: An empty string\n"
           "Given string \"\"\n"
           "Expect string \"\"\n"
           "With Method 'b'\n")
{
    string str = "";
    string ans = "";
    char method = 'b';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-both 9: String that becomes empty\n"
           "Given string \"  \\t\\t\\n\\v\\f\\r  \"\n"
           "Expect string \"\"\n"
           "With Method 'B'\n")
{
    string str = "  \t\t\n\v\f\r  ";
    string ans = "";
    char method = 'B';

    trimString( str, method );
    REQUIRE( str == ans );
}



/******************************************************************************
 * TrimString test case that have invalid methods 
 *****************************************************************************/
TEST_CASE( "trimString-invalid 1: Invalid uppercase characters\n"
           "Given string \\\"   Do not touch   \\\"\n"
           "Expect string \\\"   Do not touch   \\\"\n"
           "With invalid Method 'V'\n")
{
    string str = "   Do not touch   ";
    string ans = "   Do not touch   ";
    char method = 'V';

    trimString( str, method );
    REQUIRE( str == ans );
}
TEST_CASE( "trimString-invalid 2: Invalid lowercase characters\n"
           "Given string \\\"   Do not touch   \\\"\n"
           "Expect string \\\"   Do not touch   \\\"\n"
           "With invalid Method 'c'\n")
{
    string str = "   Do not touch   ";
    string ans = "   Do not touch   ";
    char method = 'c';

    trimString( str, method );
    REQUIRE( str == ans );
}

TEST_CASE( "trimString-invalid 3: Invalid digit\n"
           "Given string \\\"   Do not touch   \\\"\n"
           "Expect string \\\"   Do not touch   \\\"\n"
           "With invalid Method '1'\n")
{
    string str = "   Do not touch   ";
    string ans = "   Do not touch   ";
    char method = '1';

    trimString( str, method );
    REQUIRE( str == ans );
}


/*****************************************************************************/
/*****************************************************************************/
/*******************   testing string extract name   *************************/
/*****************************************************************************/
/*****************************************************************************/

/********************************************************************
 * extractStringNames test Cases for Last, First Middle 
 *******************************************************************/
TEST_CASE( "extractStringNames-lfm 1: Just a persons full name\n"
           "Given name = \"Schrader, Roger Lewis\"\n"
           "Expect first=Roger  middle=Lewis  last=Schrader")
{
    string name = "Schrader, Roger Lewis";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}



TEST_CASE( "extractStringNames-lfm 2: Just a persons full name\n"
           "Spaces before and after name\n"
           "Given name = \"   Schrader, Roger Lewis   \"\n"
           "Expect first=Roger  middle=Lewis  last=Schrader")
{
    string name = "   Schrader, Roger Lewis   ";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-lfm 3: Just a persons full name\n"
           "Spaces before, after and in the middle of the name\n"
           "Given name = \"   Schrader,   Roger   Lewis   \"\n"
           "Expect first=Roger  middle=Lewis  last=Schrader")
{
    string name = "   Schrader,   Roger   Lewis   ";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-lfm 4: Just a persons full name\n"
           "Spaces & tabs before, after and in the middle of the name\n"
           "Given name = \" \\t\\t Schrader, \\t Roger \\t Lewis \\t\\t \"\n"
           "Expect first=Roger  middle=Lewis  last=Schrader")
{
    string name = " \t\t Schrader, \t Roger \t Lewis \t\t ";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-lfm 5: Just a single characters in full name\n"
           "spaces and tabs in front, middle and end of the name\n"
           "Given name = \" \\t S, \\t R \\t L \\t \"\n"
           "Expect first=R  middle=L  last=S")
{
    string name = " \t\t S, \t R \t L \t\t ";
    string firstAnswer = "R";
    string middleAnswer = "L";
    string lastAnswer = "S";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}







/********************************************************************
 * extractStringNames test Cases for Last, First 
 *******************************************************************/
TEST_CASE( "extractStringNames-lf 1: Just a persons full name\n"
           "Given name = \"Schrader, Roger\"\n"
           "Expect first=Roger  middle=  last=Schrader")
{
    string name = "Schrader, Roger";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}

TEST_CASE( "extractStringNames-lf 2: Just a persons full name\n"
           "Spaces before and after name\n"
           "Given name = \"   Schrader, Roger   \"\n"
           "Expect first=Roger  middle=  last=Schrader")
{
    string name = "   Schrader, Roger   ";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-lf 3: Just a persons full name\n"
           "Spaces before, after and in the middle of the name\n"
           "Given name = \"   Schrader,   Roger   \"\n"
           "Expect first=Roger  middle=  last=Schrader")
{
    string name = "   Schrader,   Roger   ";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-lf 4: Just a persons full name\n"
           "Spaces before, after and in the middle of the name\n"
           "Given name = \" \\t Schrader, \\t Roger \\t\\t \"\n"
           "Expect first=Roger  middle=  last=Schrader")
{
    string name = " \t\t Schrader, \t Roger \t\t ";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-lf 5: Just a single characters in full name\n"
           "Given name = \" \\t\\t S, \\t\\t R \\t\\t \"\n"
           "Expect first=Roger  middle=  last=Schrader")
{
    string name = " \t\t S, \t\t R \t\t ";
    string firstAnswer = "R";
    string middleAnswer = "";
    string lastAnswer = "S";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}



/********************************************************************
 * extractStringNames test Cases for First Middle Last
 *******************************************************************/
TEST_CASE( "extractStringNames-fml 1: Just a full name\n"
           "Given name = \"Roger Lewis Schrader\"\n"
           "Expect first=Roger  middle=Lewis   last=Schrader")
{
    string name = "Roger Lewis Schrader";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fml 2: Just a persons full name\n"
           "Spaces before and after name\n"
           "Given name = \"   Roger Lewis Schrader   \"\n"
           "Expect first=Roger  middle=Lewis  last=Schrader")
{
    string name = "   Roger Lewis Schrader   ";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fml 3: Just a persons full name\n"
           "Spaces before, after and in the middle of the name\n"
           "Given name = \"   Roger   Lewis   Schrader   \"\n"
           "Expect first=Roger  middle=Lewis  last=Schrader")
{
    string name = "   Roger   Lewis   Schrader";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fml 4: Just a persons full name\n"
           "Spaces & tabs before, after and in the middle of the name\n"
           "Given name = \" \\t\\t Roger \\t Lewis \\t Schrader \\t\\t \"\n"
           "Expect first=Roger  middle=Lewis  last=Schrader")
{
    string name = " \t\t Roger \t Lewis Schrader \t\t ";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fml 5: Just a single characters in full name\n"
           "spaces and tabs in front, middle and end of the name\n"
           "Given name = \" \\t R \\t L \\t S \\t \"\n"
           "Expect first=R  middle=L  last=S")
{
    string name = " \t\t R \t L \t S \t\t ";
    string firstAnswer = "R";
    string middleAnswer = "L";
    string lastAnswer = "S";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer);
}



/********************************************************************
 * extractStringNames test Cases for First Last
 *******************************************************************/
TEST_CASE( "extractStringNames-fl 1: Just a full name\n"
           "Given name = \"Roger Schrader\"\n"
           "Expect first=Roger  middle=   last=Schrader")
{
    string name = "Roger Schrader";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fl 2: Just a persons full name\n"
           "Spaces before and after name\n"
           "Given name = \"   Roger Schrader   \"\n"
           "Expect first=Roger  middle=   last=Schrader")
{
    string name = "   Roger Schrader   ";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fl 3: Just a persons full name\n"
           "Spaces before, after and in the middle of the name\n"
           "Given name = \"   Roger   Schrader   \"\n"
           "Expect first=Roger  middle=   last=Schrader")
{
    string name = "   Roger   Schrader";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fl 4: Just a persons full name\n"
           "Spaces & tabs before, after and in the middle of the name\n"
           "Given name = \" \\t\\t Roger \\t  \\t Schrader \\t\\t \"\n"
           "Expect first=Roger  middle=   last=Schrader")
{
    string name = " \t\t Roger \t \t Schrader \t\t ";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer );
}
TEST_CASE( "extractStringNames-fl 5: Just a single characters in full name\n"
           "spaces and tabs in front, middle and end of the name\n"
           "Given name = \" \\t R \\t  \\t S \\t \"\n"
           "Expect first=R  middle=   last=S")
{
    string name = " \t\t R \t  \t S \t\t ";
    string firstAnswer = "R";
    string middleAnswer = "";
    string lastAnswer = "S";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer);
}



/********************************************************************
 * Test case that are tougher, these are not required
 *******************************************************************/
TEST_CASE( "extraCr extractStringNames-fml 1: Contain all whitespace possible"
           "throughout the name\n"
           "Given Name = \" \\t\\n\\v\\f\\r Roger \\t\\n\\v\\f\\r Lewis"
                          " \\t\\n\\v\\f\\r Schrader \\t\\n\\v\\f\\r \"\n"
           "Expect first=Roger   middle=Lewis    last=Schrader")
{
    string name = " \t\n\v\f\r Roger \t\n\v\f\r "
                  "Lewis \t\n\v\f\r Schrader \t\n\v\f\r ";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer);
}
TEST_CASE( "extraCr extractStringNames-fl 2: Contain all whitespace possible"
           "throughout the name\n"
           "Given Name = \" \\t\\n\\v\\f\\r Roger \\t\\n\\v\\f\\r "
                          "Schrader \\t\\n\\v\\f\\r \"\n"
           "Expect first=Roger   middle=    last=Schrader")
{
    string name = " \t\n\v\f\r Roger \t\n\v\f\r Schrader \t\n\v\f\r ";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer);
}
TEST_CASE( "extraCr extractStringNames-lfm 3: Contain all whitespace possible"
           "throughout the name\n"
           "Given Name = \" \\t\\n\\v\\f\\r Schrader, \\t\\n\\v\\f\\r Roger"
                          " \\t\\n\\v\\f\\r Lewis \\t\\n\\v\\f\\r \"\n"
           "Expect first=Roger   middle=Lewis    last=Schrader")
{
    string name = " \t\n\v\f\r Schrader, \t\n\v\f\r "
                  "Roger \t\n\v\f\r Lewis \t\n\v\f\r ";
    string firstAnswer = "Roger";
    string middleAnswer = "Lewis";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer);
}
TEST_CASE( "extraCr extractStringNames-lf 4: Contain all whitespace possible"
           "throughout the name\n"
           "Given Name = \" \\t\\n\\v\\f\\r Schrader, \\t\\n\\v\\f\\r Roger"
                          " \\t\\n\\v\\f\\r \"\n"
           "Expect first=Roger   middle=    last=Schrader")
{
    string name = " \t\n\v\f\r Schrader, \t\n\v\f\r Roger \t\n\v\f\r ";
    string firstAnswer = "Roger";
    string middleAnswer = "";
    string lastAnswer = "Schrader";
    string first, middle, last;

    extractStringNames(name, first, middle, last);

    CHECK( first == firstAnswer );
    CHECK( middle == middleAnswer );
    CHECK( last == lastAnswer);
}
