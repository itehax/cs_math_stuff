#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
  char write_msg[BUFFER_SIZE] = "Ciao bella";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  if (pipe(fd) == -1) {
    return EXIT_FAILURE;
  }
  pid_t pid = fork();
  if (pid < 0) {
    return EXIT_FAILURE;
  } else if (pid == 0) {
    close(fd[WRITE_END]);
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    printf("Read %s\n", read_msg);
    close(fd[READ_END]);
  } else {
    close(fd[READ_END]);
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
    close(fd[WRITE_END]);
  }
}
