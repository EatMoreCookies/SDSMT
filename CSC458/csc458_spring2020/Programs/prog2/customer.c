#include "customer.h"

/* This function checks to see if the request by the customer 
   can be granted. It checks this by use of the Banker's 
   Algorithm. If it can not it returns a -1, else it returns
   a 0.
*/
int request_resources(int customer_num, int request[])
{
    /* Technically we should check to see if our request > need.
    However, for this program, our request is always bounded by our need 
    when we create it. So we don't bother with it right now.*/
    
    /* See if there is enough avaiable right now to fullfil 
       the process's request */
    if( compare_request( request, available ) )
    {
        return -1;
    }

    /* temporaily change the resources to see if we can actually grant
       the request */
    temp_change_resources( customer_num, request );

    /* if the safty test fails, we must restore the system */
    if( safty_test( customer_num ) )
    {
        temp_undo_resources( customer_num, request );
        return -1;
    }   
    
    /* else we were successful */
    return 0;
}

/* Release the request by the process back to the need,
   allocation, and available arrays */
int release_resources(int customer_num, int release[])
{
    printf( "P%d released <", customer_num );

    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
    {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];

        printf( "%d", release[i] );

        if( ( i + 1 ) % NUMBER_OF_RESOURCES )
            printf( ", ");

        else
            printf( ">\n");
    }
    
    return 0;
}

/* Compares two arrays to see if the one on the left is greater 
   than the one on the right */
int compare_request( int request[], int other_array[] )
{
    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i  )
        if( request[i] > other_array[i] )
            return 1;
        
    return 0;
}

/* Temporarily changes the resources. We will keep the resouces 
   like this if the request can be granted.
 */
void temp_change_resources( int customer_num , int request[] )
{
    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
    {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }
}

/* Undos changing the resources. We do this when we cannot reach a safe
   state.
 */
void temp_undo_resources( int customer_num, int release[] )
{
    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
    {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];
    }
}

