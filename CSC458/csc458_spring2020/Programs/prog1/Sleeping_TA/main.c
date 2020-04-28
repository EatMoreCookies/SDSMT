#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"
#include <stdint.h>

pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];

/**
 * Initialize all relevant data structures and
 * synchronization objects. 
 */
void init()
{   
   // Semaphore for the ta being awake
   if ( sem_init( &(ta_awake), 0, 0 ) )
      printf("error init ta_awake\n"); 
   
   // Semaphore for the ta being available
   if ( sem_init( &(ta_available), 0, 0 ) )
      printf("error init ta_available\n"); 
   
   // Semaphore for the chairs
   if ( sem_init( &(chairs), 0, 3 ) )
      printf("error init ta_available\n");
	
   // Initialize the mutex locks.
   if ( pthread_mutex_init( (&mutex_lock), NULL ) )
      printf("error init ta\n");

   // Not necessary, but we will create id's for the threads.
   for (int i = 0; i < NUM_OF_STUDENTS; i++)
      students[i] = i;
}

void create_students()
{
   // Create all student threads.
   for (int i = 0; i < NUM_OF_STUDENTS; i++) 
   {
      // Creating unique id's for the students.
      student_ids[i] = i;
      // Create student threads. Sorry about the weird, intptr_t case. Needed to get
      // rid of a warning.
      pthread_create( &(students[i]), NULL, &student_loop, (void*)(intptr_t)student_ids[i] );
      
   }
}

void create_ta()
{
   // Create ta thread.
   pthread_create( &(ta), NULL,  &ta_loop, NULL );
}

int main(void)
{
   int i;
   waiting_students = 0;

   // Call necessary methods.
   init();
   create_ta();
   create_students();

   // Join all threads.
   pthread_join( ta, NULL );
   for ( i = 0; i < NUM_OF_STUDENTS; i++ )
   {
      pthread_join( students[i], NULL );
   }

   /* when all students have finished, we will cancel the TA thread */	
   if (pthread_cancel(ta) != 0)
      printf("%s\n",strerror(errno));

   return 0;
}