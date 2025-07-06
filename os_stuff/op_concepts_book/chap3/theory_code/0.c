#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char **argv) {
  pid_t pid;

  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Fork failed\n");
    return EXIT_FAILURE;
  } else if (pid == 0) {
    puts("About to get replaced D:");
    printf("currently i am %s\n", argv[0]);
    execlp("/bin/ls", "ls", "-la", NULL);
  } else {
    wait(NULL);
    puts("Child complete");
  }
  return 0;
}
