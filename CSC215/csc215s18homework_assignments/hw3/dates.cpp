/******************************************************************************
* Name: Fagrey, Nathaniel 
* ID: 7416949
* Section: M0002
* Homework 2
*****************************************************************************/

#include<iostream>
#include<iomanip>
#include"dates.h"
using namespace std;


int compressDate(int month, int day, int year)
{
	int date = 0;

	//use OR operator on date to add year onto it
	date = date | year;
	
	//shift 4 for month 
	date = date << 4;
	
	//use OR operator to add month on 
	date = date | month;

    //shift 6 for day
	date = date << 6;

	//use OR operator add day 
	date = date | day;

	
    return date;
}

void extractDate(int date, int &month, int &day, int &year)
{
    int yearMask = 4095;
	int monthMask = 15;
	int dayMask = 63;

	//get the day number out 
	day = date & dayMask;
    
	//shift 6
	date = date >> 6;

	//get the month number out 
	month = date & monthMask;

	//shift 4
	date = date >> 4;

	//get the year number out
	year = date & yearMask;

}

/*
Test Case 1: 5 24 2018
Combined Date: 2066776        00000000 00011111 10001001 01011000
Day  :   24                                                011000
Month:   5                                            01 01
Year :   2018                            011111 100010

Test Case 2: 1 1 2001         00000000 00011111 01000100 01000001
Combined Date: 2049089
Day  :    1                                                000001
Month:    1                                           00 01
Year :    2001                           011111 010001

Test Case 3: 8 31 1990        00000000 00011111 00011010 00011111
Combined Date: 2038303
Day  :   31                                                011111
Month:   8                                            10 00
Year :   1990                            011111 000110
*/