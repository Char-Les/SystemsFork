#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int child() {
  printf("Child process %d began\n", getpid());
  int r = ((int) rand() % 15) + 5;
  sleep(r);
  printf("Child process %d completed\n", getpid());
  return r;
}

int main() {
  printf("Parent process %d began\n", getpid());

  srand(time(NULL));
  int status = 0;

  if (fork() == 0) {
    return child();
  } else if (fork() == 0) {
    return child();
  } else {
    pid_t pid = wait(&status);
    if (WIFEXITED(status)) {
      int returned = WEXITSTATUS(status);
      printf("Child process %d slept for %d seconds\nParent process completed\n", pid, returned);
      return 0;
    }
  }
}
