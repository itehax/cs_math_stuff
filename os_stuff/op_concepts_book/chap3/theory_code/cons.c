#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main() {
  int fd = shm_open("SHARED_SHIT", O_RDWR, 0666);
  char *mem = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  printf("%s\n", (char *)mem);
  shm_unlink("SHARED_SHIT");
  return 0;
}
