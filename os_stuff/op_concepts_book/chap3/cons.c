#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main() {
  int fd = shm_open("SHARED_SHIT", O_RDWR, 0666);
  /* memory map the shared memory object */
  char *mem = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  /* read from the shared memory object */
  printf("%s\n", (char *)mem);
  /* remove the shared memory object */
  shm_unlink("SHARED_SHIT");
  return 0;
}
