#ifndef BANK_H
#define BANK_H

#include<stdio.h>
#include<stdlib.h>

/* these may be any values >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
#define RAND_BASE  10

/* Mutex Lock */
pthread_mutex_t lock;

/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* A copy for the available array */
int work[NUMBER_OF_RESOURCES];

/* Runs the banker's algorithm to determine if a request is valid */
int safty_test( int customer_num );

/* out puts all the information to the screen */
void output( int customer_num, int request[] );

/* Function to see if how many spaces we need to print */
void do_spacing( int arr[], int size, int base );

#endif