#ifndef TA_H
#define TA_H
/**
 * Header file for sleeping TA
 */

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


/* the maximum time (in seconds) to sleep */
#define MAX_SLEEP_TIME         5

/* number of maximum waiting students */
#define MAX_WAITING_STUDENTS   3

/* number of potential students */
#define NUM_OF_STUDENTS        5

/* number of available seats */
#define NUM_OF_SEATS           3

/* semaphores and mutex lock */
pthread_mutex_t mutex_lock;

/* semaphore declarations */
sem_t ta_awake;
sem_t ta_available;
sem_t chairs;

/* the number of waiting students */
int waiting_students;

/* the numeric id of each student */
int student_ids[NUM_OF_STUDENTS];

/* student function prototype */
void *student_loop(void *param);

/* ta function prototype */
void *ta_loop(void *param);

/* Student being helped */
long student_helped;

void help_student( int sleeptime );
void hang_out(int lnumber, int sleep_time);

#endif
