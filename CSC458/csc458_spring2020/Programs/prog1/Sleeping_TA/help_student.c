/**
 * Simulate helping a student
 */

#include <stdio.h>
#include "ta.h"

void help_student( int sleep_time )
{
   // ta helps a student for a random number of seconds
   printf("Helping a student for %d seconds waiting students = %d\n", sleep_time, waiting_students ); 
   sleep( sleep_time );
}
