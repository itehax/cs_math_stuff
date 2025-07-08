/* rw 1 problem, ovvero il problema dei lettori e scrittori, namely: no reader
 * should wait for reading unless  the writer acquired access to data.
 *
 * Here a solution to the first one.
 */

 /* of course shared data */
semaphore rw_mutex = 1;
semaphore mutex = 1;
int read_count = 0; /* n of currently reading  */

/* writer process */
while(true) {
    wait(rw_mutex);
    // do write stuff
    signal(rw_mutex);
}

/* reader process */
while(true) {
    wait(mutex);
    read_count++;
    if(read_count == 1) {
        wait(rw_mutex);
    }
    signal(mutex);
    /* do reading stuff */
    wait(mutex);
    rea
}
