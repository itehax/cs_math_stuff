/*
   Petersen solution to the critical section problem.
   Good for learning, but doesn't really work everywhere because we have no
   guarantee that op(load,store) are atomic. So context switch can fuck up
   everything anyway.
*/
/* data shared by Pi and Pj */
#include <stdbool.h>
int turn;
bool flag[2];

int i = 1;
int j = 2;

void petersen_i() {
  while (true) {
    flag[i] = true;
    turn = j;
    while(flag[j] == true && turn == j);
    /* exec critical section of Pi */
    flag[i] = false;
    /* rem section */
  }
}
