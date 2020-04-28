/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *student_loop( void *param)
{
   /* varaibles */
   int times_through_loop = 0;

   srandom((unsigned)time(NULL));

   while ( times_through_loop < 5 ) 
   {
      hang_out( (long)param, rand() % ( MAX_SLEEP_TIME + 1 ) );

      /* acquire the mutex lock */
      if ( pthread_mutex_lock( &mutex_lock ) )
         printf("StudentA %s\n",strerror( errno ) );
      
      /* is there a seat available? */
      if( waiting_students < MAX_WAITING_STUDENTS ) 
      {         
         // Increase waiting students.
         ++waiting_students;

         printf( "\t\tStudent %ld takes a seat waiting = %d\n", (long)param, waiting_students );

         if( pthread_mutex_unlock( &mutex_lock ) )
            printf( "Unable to release mutex %s\n", strerror(errno) );

         // Wait for a chair to become available
         if ( sem_wait( &chairs ) )
            printf("StudentB %s\n",strerror( errno ) );
         
         // Everytime a new student sits down they must be sure to keep the ta
         // awake
         sem_post( &ta_awake );
         
         // Wait for a chair to become available
         if ( sem_wait( &chairs ) )
            printf("StudentC %s\n",strerror( errno ) );
         
         // Give up the ownership of a chair
         sem_post( &chairs );

         // Wait for a chair to become available
         if ( sem_wait( &chairs ) )
            printf("StudentD %s\n",strerror( errno ) );
         
         // Give up the ownership of a chair
         sem_post( &chairs );

         // Now we wait for the ta to become available
         if( sem_wait( &ta_available ) )
            printf("StudentD %s\n",strerror( errno ) );
         
         // Current student being helped
         printf("Student %ld receiving help\n", (long)param );

         // Give up ownership of chair
         sem_post( &chairs );
      } 
      
      else 
      {
         printf("\t\t\tStudent %ld will try later\n", (long)param );
         // Release mutex lock if we are not able to sit down
         if( pthread_mutex_unlock( &mutex_lock ) )
            printf( "Unable to release mutex %s\n", strerror(errno) );

      }
      
      ++times_through_loop;
   }
}

