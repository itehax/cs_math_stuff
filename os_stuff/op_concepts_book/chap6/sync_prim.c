#include <stdio.h>
/*
  pseudo for mutex, these are atomic op:
    acquire() {
        while(!available); //busy wait, this is a  spin lock, good if pass low
  time before i can acquire the lock. otherwise waisting resources. available =
  false;
    }
    release() {
        available = true;
    }

    semaphore is more sophisticated and more robut for solving the critical
  section problem. 2 main atomic op: wait(S) { while(S<=0); // busy wait S--;
    }
    signal(S) {
        S++;
    }
*/

/*
    synch is semaphore shared. at first synch=0
    example usage: given p1,p2, execute in order. how?

    IN p1=
    p1;
    signal(synch);

    IN p2=
        wait(synch);
        s2;

*/

/* a simple impl that doesnt't suffer the busy waiting desease.

    When a process must wait, the process instead of busy w can suspend itself.
    Use ready and waiting queue, process restarted(put in ready queue) by wakeup
   operation(which happens when signal is executed).
 */

typedef struct {
  int value;
  struct process *list;
} semaphore;

void wait(semaphore* S) {
    S->value--;
    if(S->value < 0) {
        // add this proc to S->list;
        // sleep();
    }
}
void signal(semaphore *S) {
    S->value++;
    if(S->value <= 0) {
        //remove proc p from S->list;
        //wakeup(P);
    }
}

/* now monitors:
  Why? locks and semaphore alone could be misused causing problem
  Eg. wait(); crit_section(); wait(); -> this will wait forever
  or for example: signal(); crit_section(); wait(); -> the signal could make start several ctrit_sections... and so on.

 Semaphore handle complexity, is ADT.  i can also define several condition for diff use cases.  book for impl and more.

 */
int main() {}
