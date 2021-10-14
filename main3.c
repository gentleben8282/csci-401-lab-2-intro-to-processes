/* CSCI 401: Lab 2: Intro to Processes
 * Programmer (Student ID): Ben Corriette (@02956064)
 * Last modified date: 10/11/2021
 * 
 * Summary: Creates two child processes, which are looped for a random number
 * no greater than 30, times, and the child process sleeps for a random number 
 * no greater than 10, seconds, per iteration, while the parent process waits.
 *
 * Reference: https://stackoverflow.com/questions/10909011/how-to-use-fork-to-create-only-2-child-processes
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


void ChildProcess()
{
  srandom(time(0));
  int upperIterationLimit = 30;
  int upperSleepLimit = 10;
  int randomIterationNumber = (random() % upperIterationLimit);
  int randomSleepNumber = (random() % upperSleepLimit);
	int sleepStatus;
  int i;
   
  // Child processes will loop for a random # (<= 30) of iterations
  for (i = 1; i <= randomIterationNumber; i++) {
    printf("Child Pid: %d is going to sleep!\n", getpid());
    sleepStatus = sleep(upperSleepLimit);
    if (sleepStatus == 0) {
      printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }
  }
  exit(0);
}

void ParentProcess()
{ 
  int childStatus;
  int terminatedChildPid = wait(&childStatus);
  
  if (terminatedChildPid > -1) {
    printf("Child Pid: %d has completed\n", terminatedChildPid); 
  }
  else {
    perror("The child process has not been successfully terminated.");
    exit(EXIT_FAILURE);
  }
}

int main()
{
	pid_t processId;
  pid_t processId2;
 
  processId = fork(); 
  if (processId > 0) {
    processId2 = fork();
    if (processId2 > 0) {
      ParentProcess();
    }
    else if (processId2 == 0) {
      ChildProcess();
    }
  }
  else if (processId == 0) {
    ChildProcess();
  }
	else {
    perror("An error has occurred while forking the process.");
    exit(EXIT_FAILURE);
  }
   
  return 0;
}