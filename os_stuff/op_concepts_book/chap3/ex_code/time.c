/*
 Write a C program called time.c that determines the amount of time
 necessary to run a command from the command line. This program will
 be run as "./time <command>" and will report the amount of elapsed
 time to run the specified command. This will involve using fork() and
 exec() functions, as well as the gettimeofday() function to determine the
 elapsed time
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define MEM_SIZE 4096
const char *MEM_NAME = "TIME_SHARED";
#define READ_END 0
#define WRITE_END 1

long get_cur_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  long time_milliseconds = (tv.tv_sec * 1000L) + tv.tv_usec / 1000L;
  return time_milliseconds;
}
//pipe approach, below there is shm approach
int main(int argc, char *argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "Expected 1 arg.\n");
    return EXIT_FAILURE;
  }
  char read_buf[MEM_SIZE];
  char write_buf[MEM_SIZE];
  strlcpy(write_buf, argv[1], MEM_SIZE);
  int fd[2];
  if (pipe(fd) == -1) {
    fprintf(stderr, "Error while creating pipes\n");
    return EXIT_FAILURE;
  }
  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Error while creating pipes\n");
    return EXIT_FAILURE;
  } else if (pid == 0) { // child

    close(fd[READ_END]);
    long cur_time = get_cur_time();
    write(fd[WRITE_END], &cur_time, sizeof(long));
    close(fd[WRITE_END]);
    execlp(argv[1], argv[1], NULL);
  } else {
    wait(NULL);
    close(fd[WRITE_END]);
    long cur = get_cur_time();
    long prev;
    read(fd[READ_END], &prev, sizeof(long));
    close(fd[READ_END]);
    printf("Time elapsed=%ld\n", cur - prev);
    return EXIT_SUCCESS;
  }
}

/* first approach uses shared mem */
// int main(int argc, char *argv[]) {
//   if (argc <= 1) {
//     fprintf(stderr, "Expected 1 arg.\n");
//     return EXIT_FAILURE;
//   }
//
//   int fd = shm_open(MEM_NAME, O_CREAT | O_RDWR, 0666);
//   ftruncate(fd, MEM_SIZE);
//   char *mem =
//       (char *)mmap(0, MEM_SIZE, PROT_READ | PROT_WRITE, //MAP_SHARED, fd, 0);
//
//   pid_t pid = fork();
//
//   if (fork < 0) {
//     fprintf(stderr, "Error while forking\n");
//     return EXIT_FAILURE;
//   } else if (pid == 0) { // child
//     long time_milliseconds = get_cur_time();
//     memcpy(mem, &time_milliseconds, sizeof(long));
//     execlp(argv[1], argv[1], NULL);
//
//   } else { // father
//
//     wait(NULL);
//     long cur = get_cur_time();
//     long prev;
//     memcpy(&prev, mem, sizeof(long));
//     printf("Time elapsed=%ld\n", cur - prev);
//     shm_unlink(MEM_NAME);
//     return EXIT_SUCCESS;
//   }
// }
