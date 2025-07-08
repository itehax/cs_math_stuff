#include <stdbool.h>
/* Atomic op: return res of test (true or false) and set to true */
bool test_and_set(bool *target) {
  bool test_res = *target;
  *target = true;
  return test_res;
}
bool lock = false; /* shared between processes */
void handle_crit_section() {
  do {
    while (test_and_set(&lock) == true)
      ; /* wait */

    /* exec critical section */
    lock = false;
  } while (true);
}

/* other approach */
int cmp_and_swap(int *value, int expected, int new_value) {
  int tmp = *value;
  if (*value == expected) {
    *value = new_value;
  }
  return tmp;
}

/* only mutual exclusion handled(2,3 prop need improved version) */
void handle_crit_section_cmp_swap() {
  while (true) {
    while (cmp_and_swap(&lock, 0, 1) != 0)
      ; /* wait */

    /* exec critical section */
    lock = false;
    /* remainder section */
  }
}

/* increment: use cmp_and_swap to implement atomic increment */

void increment(int *v) {
  int tmp;
  do {
    tmp = *v;
  } while (tmp != cmp_and_swap(v, tmp, tmp + 1));

}
