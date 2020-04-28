/**
 * General structure of the teaching assistant.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *ta_loop(void *param)
{
    /* seed random generator */
    srandom((unsigned)time(NULL));

    while ( 1 ) 
    {                
        /* wait for a student to show up */
        if( sem_wait( &ta_awake ) )
            printf("%s\n",strerror(errno));
        
        /* acquire the mutex lock */
        if ( pthread_mutex_lock( &mutex_lock) )
            printf("%s\n",strerror(errno));

        /* indicate the TA is ready to help a student */
        if( sem_post( &ta_available ) )
           printf("%s\n",strerror(errno));
        
        // Decrement waiting students here because we need to print out 
        // the correct number when we help them.
        --waiting_students;

        /* release mutex lock */
        if ( pthread_mutex_unlock( &mutex_lock ) )
            printf("%s\n",strerror(errno));
        
        help_student( rand() % ( MAX_SLEEP_TIME + 1 ) );
    }
}