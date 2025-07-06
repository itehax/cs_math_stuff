/*
 An operating system’s pid manager is responsible for managing process
 identifiers. When a process is first created, it is assigned a unique pid
 by the pid manager. The pid is returned to the pid manager when the
 process completes execution, and the manager may later reassign this
 pid.
*/
// IMPLEMENT DOUBLE LINKED LIST, DO IN FREE TIME, NOW GOTTA STUDY.
#include <math.h>
#include <stdint.h>
#define MIN_PID 300
#define MAX_PID 500
#define DELTA_PID (MAX_PID - MIN_PID)
#define SIZE                                                                   \
  (((DELTA_PID - 1) / (sizeof(uint64_t) * 8)) +                                \
   1) // knuth formula for converting from ceil to floor (C uses floor by
      // default(kinda) so, WIN!)
#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))

enum manager_status {
  EMPTY,
  AVAILABLE,
  FULL,
};

struct pid_manager {
  uint64_t pids[SIZE];
  enum manager_status status;
};


struct pid_manager manager = {.pids = {0}, .status = EMPTY};

/*
 —Allocates and returns a pid; returns −1 if unable to allocate a pid (all pids
 are in use)
*/
int allocate_pid(void) {
  if (manager.status == FULL) {
    return -1;
  }

}

/* Release a pid */
void release_pid(int pid) {}
