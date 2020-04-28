// Nathaniel Fagrey. CSC 458 Explore 1.

// Including necessary libraries.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

// gcc -g -Wall -o test test.c -lpthread 

// This function gets the current pid ( process ID ) of the child
// thread. It then outputs the pid of that child and terminates 
// the child thread.
void* thread_function(void* arg)
{
   fprintf(stderr, "Child thread pid is %d\n", (int) getpid());
   pthread_exit(0);
}
// Main function.
int main(void)   {
   // Creates variables of type pid_t.
   pid_t child_pid, wpid;   
   // Creates a variable of type pthread_t.
   pthread_t thread;
   // Minor variables.
   int status = 0;   
   int i;
   // This is just a random array, so we can show processes exiting
   // successfully and not successfully.   
   int a[3] = {1, 2, 1};

   // Out puts the parent proccess ID.
   printf("parent_pid = %d\n", getpid());
   // For 3 times... 
   for (i = 0; i < 3; i++)   {
      // Duplicates the parent process to create a child process.     
      if ((child_pid = fork()) == 0)   {
	 // Outputs that we are in a child process along with
	 // its ID.
         printf("In child process (pid = %d)\n", getpid());
         // We exit the child process with unsucessful exit code if this condition is true.
	 if (a[i] < 2)
            exit(1);
 	 // We exit the child process with sucessful exit code if this condition is true.
         else
            exit(0);
      }
   }
   	
   // Creates a new thread. With the start routine for this thread being
   // the function thread_function.
   pthread_create(&thread, NULL, &thread_function, NULL);
   // Waits for the thread specified to terminate. This thread was killed in
   // thread_function, but we are just making sure.
   pthread_join(thread, NULL);
   
   // We are waiting for all the child processes of the parent to terminate.
   while ((wpid = wait(&status)) > 0)
      // For each child process, we are looking to see if that process exited sucessfully or not.
      // Looking above at that code, you can see how we determined if a process terminated 
      // successfully. We output "accept" if it did and "reject" if it did not.
      printf("Exit status of %d was %d (%s)\n", (int)wpid, status,
               (status > 0) ? "accept" : "reject");
   // Return...obviously :)
   return 0;
}
