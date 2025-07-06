/*
 Using either a UNIX or a Linux system, write a C program that forks
 a child process that ultimately becomes a zombie process. This zombie
 process must remain in the system for at least 10 seconds.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main(void) {
  pid_t pid = fork();
  if (pid < 0) {
    return EXIT_FAILURE;
  } else if (pid == 0) {
    puts("Im dead dude");
  } else {
    sleep(10);
    wait(NULL);
    return 0;
  }
}
