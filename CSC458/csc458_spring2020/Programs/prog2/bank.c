#include "bank.h"

/* This function is the Banker's Algorithm. It attempts to find 
   an index in noth the need array and the work array 
   ( copy of available ) that satifies the equality need <= work.
   If we can find this index, the request by the customer is valid
   and we return 0. Else we return 1
*/
int safty_test( int customer_num )
{
    int finish[ NUMBER_OF_RESOURCES ];
    int work[ NUMBER_OF_RESOURCES ];
    int not_safe = 0;
    int index = 0;

    /* initialize our arrays */
    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
    {
        finish[i] = 0;
        work[i] = available[i];
    }

    /* Continually loop through until we find our index */
    while( finish[index] == 0 )
    {
        /* inequality condition */
        if( need[customer_num][index] <= work[index] )
        {
            work[index] += allocation[customer_num][index];
            finish[index] = 1;
        }

        index++;
    }

    /* Now we check to see if all places in the finish arrary our true */
    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
    {
        if( !finish[i] )
            not_safe = 1;
    }    

    /* return 1 if not safe */
    if( not_safe )
        return 1;
    
    /* else return 0 */
    return 0;
}

/* This is simply our output function. It prints everything in nice clean
   rows. Your welcome Austin :).
*/
void output( int customer_num, int request[] )
{
    printf("\n     Allocation    Need    Available\n" );

    for( int i = 0; i < NUMBER_OF_CUSTOMERS; ++i  )
    {
        printf( "P%d     ", i );

        do_spacing( allocation[i], NUMBER_OF_RESOURCES, 5 );
        
        do_spacing( need[i], NUMBER_OF_RESOURCES, 5 );

        do_spacing( available, NUMBER_OF_RESOURCES, 5 );

        printf( "\n" );
    }

    printf( "\nRequest P%d <", customer_num );

    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
    {
        printf( "%d", request[i] );

        if( ( i + 1 ) % NUMBER_OF_RESOURCES )
            printf( ", ");

        else
            printf( ">\n"); 
    }

}

/* Helper function for our output function. It makes sure
   the number of spaces is adjusted for the size of the number 
*/
void do_spacing( int arr[], int size, int base )
{
    int spaces_to_printed = base;
    int temp;

    for( int i = 0; i < size; ++i )
    {
        printf( "%d ", arr[i] );
        temp = arr[i];

        while( temp >= 10 )
        {
            temp /= 10;
            spaces_to_printed--;
        }  
    }

    for( int i = 0; i < spaces_to_printed; ++i )
            printf( " " );
}
