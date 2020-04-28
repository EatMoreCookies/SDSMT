#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "bank.h"

int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);
int compare_request( int request[], int other_array[] );
void temp_change_resources( int customer_num , int request[] );
void temp_undo_resources( int customer_num, int release[] );

#endif