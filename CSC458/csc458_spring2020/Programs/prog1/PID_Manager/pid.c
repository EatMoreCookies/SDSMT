/**
 * A solution to the pid manager problem. 
 *
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>

// Allocates the pid map.
int allocate_map(void) 
{
   for( int i = PID_MIN; i < PID_MAX; ++i )
   {
      pid_map[i] = 0; 
   }

   return 0;
}

// Allocates a pid
int allocate_pid(void)
{
   /* local variables */
   int i;
   int retVal;

   /* acquire the mutex lock and warn if unable */
   if( pthread_mutex_lock( &mutex ) )
      printf( "Unable to acquire mutex!" );

   // i is guaranteed to wrap around
   i = last % PID_MAX;

   // Set i to PID_MIN
   if( i < PID_MIN )
	   i = PID_MIN; 

   // Go until we find an open pid
   while( i < PID_MAX + 1 && pid_map[i] != 0 )
      ++i;

   // If we have not found a pid, we will return -1
   if( i == PID_MAX + 1 )
      retVal = -1;
   
   // Assign i to last, and mark it in the pid_map
   else
   {
      last = i;
      retVal = last;
      pid_map[i] = 1;
   }

   /* release and warn if the mutex was not released */
   if( pthread_mutex_unlock( &mutex ) )
      printf( "Unable to release mutex!");
      
   return retVal;
}

// Releases a pid
void release_pid(int pid)
{
   /* local variables */
   int i;

   /* acquire the mutex lock and warn if unable */
   if( pthread_mutex_lock( &mutex ) )
      printf( "Unable aquire mutex!");
   
   // Release that pid
   pid_map[pid] = 0;
   
   /* release and warn if the mutex was not released */
   if( pthread_mutex_unlock( &mutex ))
      printf( "Unable to release mutex!");
}
