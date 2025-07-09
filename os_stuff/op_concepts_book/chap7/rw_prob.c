/* rw 1 problem, ovvero il problema dei lettori e scrittori, namely: no reader
 * should wait for reading unless  the writer acquired access to data.
 *
 * Here a solution to the first one.
 */

/* of course shared data */
semaphore rw_mutex = 1; // rw
semaphore mutex = 1;    // used for working with read_count
int read_count = 0;     /* n of currently reading  */

/* writer process */
while (true) {
  wait(rw_mutex);
  // do write stuff
  signal(rw_mutex);
}

/* reader process
    first reader is placed into rw_mutex queue, other in mutex queue.
    Also, mutex is used to work with read_count
    OK, but why first reader is in rw_mutex queue? because in this way, no other
   writer could write, when readers are reading. (also note that process
   scheduler choose if after signal(rw_mutex) the reader code is going to take
   the lock, or another writer in rw_queue.)
*/
while (true) {
  wait(mutex);
  ++mutex;
  if (read_count == 1) {
    wait(rw_mutex);
  }
  signal(mutex);
  /* read stuff */
  wait(mutex);
  --read_count;
  if (read_count == 0) {
    signal(rw_mutex);
  }
  signal(mutex);
}
