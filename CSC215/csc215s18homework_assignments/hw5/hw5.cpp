/******************************************************************************
* Name: Fagrey, Nathaniel
* ID: 7416949
* Section: M0002
* Homework 5
*****************************************************************************/

#include "mystring.h"
#include<cctype>
#define CATCH_CONFIG_MAIN
#include "..\catch.hpp"

//Test cases for trim function 
TEST_CASE("Given a string \"  whitespace in front\", method =  'f' "
	"Expect: whitespace in front")
{
	char cstr[100] = "   whitespace in front";
	char answer[100] = "whitespace in front";

	trim(cstr, 'f');

	REQUIRE(strcmp(cstr, answer) == 0);
}

TEST_CASE("Given a string, \"no whitespace in front  \" , method =  'F' "
	"Expect: \"no whitespace in front  \" ")
{
	char cstr[100] = "no whitespace in front  ";
	char answer[100] = "no whitespace in front  ";

	trim(cstr, 'F');

	REQUIRE(strcmp(cstr, answer) == 0);
}

TEST_CASE("Given a string ""  , method =  'F' "
	"Expect: "" ")
{
	char cstr[100] = "";
	char answer[100] = "";

	trim(cstr, 'F');

	REQUIRE(strcmp(cstr, answer) == 0);
}


TEST_CASE("Given a string \"whitespace in back  \", method =  'e' "
	"Expect: \"whitespace in back\" ")
{
	char cstr[100] = "whitespace in back  ";
	char answer[100] = "whitespace in back";

	trim(cstr, 'e');

	REQUIRE(strcmp(cstr, answer) == 0);
}

TEST_CASE("Given a string \"   whitespace in back  \", method =  'E' "
	"Expect: \"   whitespace in back  \" ")
{
	char cstr[100] = "   whitespace in back  ";
	char answer[100] = "   whitespace in back";

	trim(cstr, 'E');

	REQUIRE(strcmp(cstr, answer) == 0);
}

TEST_CASE("Given a string "", method =  'E' "
	"Expect:  "" ")
{
	char cstr[100] = "";
	char answer[100] = "";

	trim(cstr, 'E');

	REQUIRE(strcmp(cstr, answer) == 0);
}

TEST_CASE("Given a string \"\n  whitespace in both \", method =  'b' "
	"Expect: \"whitespace in back\" ")
{
	char cstr[100] = "\n  whitespace in both  ";
	char answer[100] = "whitespace in both";

	trim(cstr, 'b');

	REQUIRE(strcmp(cstr, answer) == 0);
}

TEST_CASE("Given a string \"whitespace in back\", method =  'B' "
	"Expect: \"whitespace in back\" ")
{
	char cstr[100] = "whitespace in back";
	char answer[100] = "whitespace in back";

	trim(cstr, 'B');

	REQUIRE(strcmp(cstr, answer) == 0);
}

TEST_CASE("Given a string "       ", method =  'B' "
	"Expect: "" ")
{
	char cstr[100] = "";
	char answer[100] = "";

	trim(cstr, 'B');

	REQUIRE(strcmp(cstr, answer) == 0);
}




//Test Cases for extractNames function. 
TEST_CASE("Given string: \"  Nate Ed Fagrey  \" , expect first = Nate, Middle = \"Ed\" "
	"last = fagrey")
{
	char str[] = " Nate Ed Fagrey  ";
	char first[100] = "";
	char middle[100] = "";
	char last[100] = "";
	char fanswer[100] = "Nate";
	char manswer[100] = "Ed";
	char lanswer[100] = "Fagrey";

	extractNames(str, first, middle, last);
	
	REQUIRE(strcmp(fanswer, first) == 0);
	REQUIRE(strcmp(manswer, middle) == 0);
	REQUIRE(strcmp(lanswer, last) == 0);
}

TEST_CASE("Given string: \"  Nate Fagrey  \" , expect first = Nate, middle = "" "
	"last = fagrey")
{
	char str[] = " Nate Fagrey  ";
	char first[100] = "";
	char middle[100] = "";
	char last[100] = "";
	char fanswer[100] = "Nate";
	char manswer[100] = "";
	char lanswer[100] = "Fagrey";

	extractNames(str, first, middle, last);

	REQUIRE(strcmp(fanswer, first) == 0);
	REQUIRE(strcmp(manswer, middle) == 0);
	REQUIRE(strcmp(lanswer, last) == 0);
}

TEST_CASE("Given string: \"  Fagrey, Nate Ed   \" , expect first = Nate, middle = Ed "
	"last = Fagrey")
{
	char str[] = " Fagrey, Nate Ed  ";
	char first[100] = "";
	char middle[100] = "";
	char last[100] = "";
	char fanswer[100] = "Nate";
	char manswer[100] = "Ed";
	char lanswer[100] = "Fagrey";

	extractNames(str, first, middle, last);

	REQUIRE(strcmp(fanswer, first) == 0);
	REQUIRE(strcmp(manswer, middle) == 0);
	REQUIRE(strcmp(lanswer, last) == 0);
}

TEST_CASE("Given string: \"  Fagrey, Nate   \" , expect first = Nate, middle = "" "
	"last = fagrey")
{
	char str[] = " Fagrey, Nate  ";
	char first[100] = "";
	char middle[100] = "";
	char last[100] = "";
	char fanswer[100] = "Nate";
	char manswer[100] = "";
	char lanswer[100] = "Fagrey";

	extractNames(str, first, middle, last);

	REQUIRE(strcmp(fanswer, first) == 0);
	REQUIRE(strcmp(manswer, middle) == 0);
	REQUIRE(strcmp(lanswer, last) == 0);
}

TEST_CASE("Given string: \"  Nate   \" , expect first = Nate, middle = "" "
	"last = fagrey")
{
	char str[] = "  Nate  ";
	char first[100] = "";
	char middle[100] = "";
	char last[100] = "";
	char fanswer[100] = "Nate";
	char manswer[100] = "";
	char lanswer[100] = "";

	extractNames(str, first, middle, last);

	REQUIRE(strcmp(fanswer, first) == 0);
	REQUIRE(strcmp(manswer, middle) == 0);
	REQUIRE(strcmp(lanswer, last) == 0);
}

TEST_CASE("Given string: \"  Fagrey,   \" , expect first = Nate, middle = "" "
	"last = fagrey")
{
	char str[] = "  Fagrey,  ";
	char first[100] = "";
	char middle[100] = "";
	char last[100] = "";
	char fanswer[100] = "";
	char manswer[100] = "";
	char lanswer[100] = "Fagrey";

	extractNames(str, first, middle, last);

	REQUIRE(strcmp(fanswer, first) == 0);
	REQUIRE(strcmp(manswer, middle) == 0);
	REQUIRE(strcmp(lanswer, last) == 0);
}