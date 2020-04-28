#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "bank.h"
#include "customer.h"


/* This function just creates a array of random integers
   that are bound by the contents of the second array.
*/
void create_rand_array( int* arr, int* bounded_arr )
{
    for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
    {
        int temp = bounded_arr[i];
        
        if( temp == 0 )
            arr[i] = temp;

        else 
            arr[i] = rand() % ( temp + 1 );
    }
}

/* Thread function. It create a request and acquires a mutex lock.
   It then asks to check to see if its request can be granted. If it
   can, we print so, else we print unsuccessful. We only release resouces
   when a process gets all the resources it requires.
*/
void* customer( void *param )
{
    int request[NUMBER_OF_RESOURCES];
    int release[NUMBER_OF_RESOURCES];
    int sum;

    while( 1 )
    {   
        sum = 0;
        
        /* Add up the need for the customer */
        for( int i = 0; i < NUMBER_OF_RESOURCES; ++i )
            sum += need[(int)(intptr_t)param][i];

        /* If the need is zero, the process releases all of its resources */
        if( sum == 0 )
        {
           release_resources( (int)(intptr_t)param, allocation[(int)(intptr_t)param] );
           pthread_exit( param );
        }

        else
        {
            /* Randomly creates a request that is bounded by the need of that
               customer 
            */
            create_rand_array( request, need[ (int)(intptr_t)param ] );
            
            /* Acquire mutex lock */
            if( pthread_mutex_lock( &lock ) )
                printf( "\nunable to aquire mutex!\n");
                
            /* Print the current state of the system */
            output( (int)(intptr_t)param, request );

            /* See if request can be granted */
            if( request_resources( (int)(intptr_t)param, request ) == -1 )
            {
                printf( "Unsafe! Request NOT granted\n" );
            }

            else
            {
                printf( "Safe. Request granted\n" );
            }

            /* Randomly creates a release that is bounded by the allocation
               of that customer 
            */
            create_rand_array( release, allocation[(int)(intptr_t)param] );

            /* Release those random resources */
            release_resources( (int)(intptr_t)param, release );
                    
            /* Release mutex lock */
            if( pthread_mutex_unlock( &lock ) )
                printf( "\nunable to release mutex!\n");
            
            /* Randomly sleep so the simulation is more realistic */
            sleep( rand() % 5 );
        }
    }
}

/* Initializes all our data structure */
void init_resources( )
{
    /* Init mutex lock */
    if( pthread_mutex_init( &lock, NULL ) )
    {
      printf("\nmutex init failed!\n");
    }
    
    /* Initialize all data structure */
    for( int i = 0; i < NUMBER_OF_CUSTOMERS; ++i )
    {   
        for( int j = 0; j < NUMBER_OF_RESOURCES; ++j )
        {
            maximum[i][j] = rand() % RAND_BASE;
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }    
}

int main( int argc, char **argv )
{
    int temp = argc;
    pthread_t tids[ NUMBER_OF_CUSTOMERS ];
    srand(time( NULL) );

    /* Make sure the correct number of arguments was given */
    if( argc <= 1 )
    {
        printf( "Insufficient arguments given!\nExiting now...\n");
        return 1;
    }

    /* Copy arguments from the command line to our availble array */
    while( temp > 1 )
    {
        available[ argc-temp ] = atoi(argv[ argc - temp + 1 ] );
        temp--;
    }

    /* Fill the necessary arrays */
    init_resources( );

    /* Create the threads */
    for( int i = 0; i < NUMBER_OF_CUSTOMERS; ++i )
    {
        tids[i] = i;
        pthread_create( &( tids[i] ), NULL, &customer, (void*)(intptr_t) tids[i] );
    }

    /* Run the threads */
    for( int i = 0; i < NUMBER_OF_CUSTOMERS; ++i )
    {
        pthread_join( tids[i], NULL );
    }

    return 0;
}