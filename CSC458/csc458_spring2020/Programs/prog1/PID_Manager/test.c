/**
 * test.c
 *
 * Test the implementation of the PID manager.
 *
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pid.h"

#define NUM_THREADS 100
#define ITERATIONS   10
#define SLEEP         5

// in_use array for testing for duplicate pid's
int in_use[PID_MAX + 1];
pthread_mutex_t test_mutex;

void *allocator(void *param)
{
   int i, pid;

   for (i = 0; i < ITERATIONS; i++) 
   {
      /* sleep for a random period of time */
		sleep((int)(random() % SLEEP));

      /* allocate a pid */
      pid = allocate_pid( );

      // Print if no pid available, but keep going
      if (pid == -1)
         printf("No pid available\n");
      
      else 
      {
         // Aquire lock for testing to make sure we do not allocate
         // duplicate pid's
         if( pthread_mutex_lock( &test_mutex ) )
            printf( "Unable to aquire mutex_lock!" );
         
         // Print error message if we are assigned a duplicate pid
         if( in_use[pid] != 0 )
         {
            printf( "DUPLICATE PID DETECTED!");
         }
         
         else
            in_use[pid] = 1;

          /* indicate in the in_use map the pid is in use */
         printf( "allocated %d\n", pid );

         // Release the test_mutex
         if( pthread_mutex_unlock( &test_mutex ) )
            printf( "Unable to release mutex_lock!" );
         
         /* sleep for a random period of time */
         sleep((int)(random() % SLEEP));         
         
         // Reaquire this lock so we can change the value of 
         // the in_use array
         if( pthread_mutex_lock( &test_mutex ) )
            printf( "Unable to aquire mutex_lock!" );
         
         /* release the pid */
         release_pid( pid );

         // Unmark in_use
         in_use[pid] = 0;

         printf( "released %d\n", pid );

         // Release the test_mutex
         if( pthread_mutex_unlock( &test_mutex ) )
            printf( "Unable to release mutex_lock!" );
      }
   }
}

int main(void)
{
   printf("last is %d\n", last);
   int i, error;
   pthread_t tids[NUM_THREADS];

   last = PID_MIN;

   // Initialize the in_use array to 0's
   for( i = 0; i < PID_MAX + 1; ++i )
      in_use[i] = 0;

   /* allocate the pid map */
   if (allocate_map() == -1)
      return -1;

   srandom((unsigned)time(NULL));

   // Initialize the mutex used for pid allocation and release
   if(pthread_mutex_init(&mutex, NULL) != 0) 
   {
      printf("\n mutex init failed\n");
   }

   // Initialize the mutex used for testing
   if( pthread_mutex_init( &test_mutex, NULL ) != 0 )
   {
      printf("\n mutex init failed\n");
   }

   i = 0;
   // Create all our threads
   while ( i < NUM_THREADS ) 
   {
      if( pthread_create( &(tids[i]), NULL, &allocator, NULL ) )
         printf("\nThread can't be created");
      
      ++i;
   }

   i = 0;
   // Run all threads
   while( i < NUM_THREADS )
   {
      pthread_join( tids[i], NULL);
      ++i;
   }

   // Destroy mutex.
   pthread_mutex_destroy(&mutex);
   // Destroy test_mutex
   pthread_mutex_destroy(&test_mutex);

   return 0;
}
