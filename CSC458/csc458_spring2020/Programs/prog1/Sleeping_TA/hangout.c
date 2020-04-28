/**
 * Simulate a student hanging out
 */

#include <stdio.h>
#include "ta.h"

void hang_out(int lnumber, int sleep_time) 
{
   // Student goes back to programming for a random number of seconds
   // before checking back with the ta
   printf("\tStudent %d hanging out for %d seconds\n", lnumber, sleep_time );
   sleep( sleep_time );
}