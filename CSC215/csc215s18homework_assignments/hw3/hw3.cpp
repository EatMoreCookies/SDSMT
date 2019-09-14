#include "dates.h"  
#define CATCH_CONFIG_MAIN 
#include "..\\catch.hpp" 
using namespace std; 

//place test cases here
TEST_CASE("compressDate: given 5 24 2018 . Expect 2066776")
{
	int month = 5;
	int day = 24;
	int year = 2018;

	REQUIRE(compressDate(month, day, year) == 2066776);
}

TEST_CASE("extractDate: given 2066776. Expect month = 5, day = 24, year = 2018")
{
	int date = 2066776;
	int year = 0;
	int month = 0;
	int day = 0;

	extractDate(date, month, day, year);

	REQUIRE(month == 5);
	REQUIRE(day == 24);
	REQUIRE(year == 2018);

}

TEST_CASE("compressDate: given 1 1 2001. Expect 2049089")
{
	int month = 1;
	int day = 1;
	int year = 2001;

	REQUIRE(compressDate(month, day, year) == 2049089);
}

TEST_CASE("extractDate: given 2049089. Expect month = 1, day = 1, year = 2001")
{
	int date = 2049089;
	int year = 0;
	int month = 0;
	int day = 0;

	extractDate(date, month, day, year);

	REQUIRE(month == 1);
	REQUIRE(day == 1);
	REQUIRE(year == 2001);

}

TEST_CASE("compressDate: given 8 31 1990. Expect 2038303")
{
	int month = 8;
	int day = 31;
	int year = 1990;

	REQUIRE(compressDate(month, day, year) == 2038303);
}

TEST_CASE("extractDate: given 2038303. Expect month = 8, day = 31, year = 1990")
{
	int date = 2038303;
	int year = 0;
	int month = 0;
	int day = 0;

	extractDate(date, month, day, year);

	REQUIRE(month == 8);
	REQUIRE(day == 31);
	REQUIRE(year == 1990);

}

//trying to make the test case fail
TEST_CASE("compressDate: given 12 31 4000. Expect 4096799")
{
	int month = 12;
	int day = 31;
	int year = 4000;

	REQUIRE(compressDate(month, day, year) == 4096799);
}

TEST_CASE("extractDate: given 4096799. Expect month = 12, day = 31, year = 4000")
{
	int date = 4096799;
	int year = 0;
	int month = 0;
	int day = 0;

	extractDate(date, month, day, year);

	REQUIRE(month == 12);
	REQUIRE(day == 31);
	REQUIRE(year == 4000);

}

