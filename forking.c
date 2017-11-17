#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

/*
  Joshua Turcotti Charles Weng
  Systems - 4
  HW 12 - Please Fork Responsibly
*/

// this is what the child does
int child() {
  printf("Child process %d began\n", getpid());
  // go through the seeded rand a unique amount of times
  int x = getpid();
  for(x; x > 0; x--){
    rand();
  }
  // get the sleep time and sleep; afterwards return the sleep time
  int r = ((int) rand() % 15) + 5;
  sleep(r);
  printf("Child process %d completed\n", getpid());
  return r;
}

int main() {
  printf("Parent process %d began\n", getpid());
  // seed the rand() function
  srand(time(NULL));
  int status = 0;

  // forks off one child and parent goes to the next check
  if (fork() == 0) {
    return child();
    // fork off another child and parent goes to the next check
  } else if (fork() == 0) {
    return child();
  } else {
    // wait for a child
    pid_t pid = wait(&status);
    // if there is a return status
    if (WIFEXITED(status)) {
      int returned = WEXITSTATUS(status);
      printf("Child process %d slept for %d seconds\nParent process completed\n", pid, returned);
    }
    return 0;
  }
}
