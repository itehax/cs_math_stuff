#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int fd = shm_open("SHARED_SHIT", O_CREAT | O_RDWR, 0666);
  ftruncate(fd, 4096);
  char *mem = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  char *msg_1 = "ciao bella";
  char *msg_2 = "bella ciao";
  sprintf(mem, "%s", msg_1);
  mem += strlen(msg_1) + 1;
  sprintf(mem, "%s", msg_2);
  mem += strlen(msg_2) + 1;
  while (1)
    ;
  return 0;
}
