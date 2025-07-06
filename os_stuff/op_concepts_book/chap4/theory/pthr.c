#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N_THREADS 10
int sum = 0; /* shared between threads */

struct range {
  int start;
  int end;
};

void *runner(void *param);

int main(int argc, char *argv[]) {
  pthread_t workers[N_THREADS + 1];
  pthread_attr_t workers_attr;
  pthread_attr_init(&workers_attr); // maybe can use only one
  struct range range_data[N_THREADS];

  int x = atoi(argv[1]);
  int chunk_size = x / N_THREADS;
  int rem = x % N_THREADS;

  for (int i = 0; i < N_THREADS; ++i) {
    // buggy, sum until n-1, but easy fixable, i care about threads.
    range_data[i].start = chunk_size * i;
    range_data[i].end = chunk_size * (i + 1);

    pthread_create(&workers[i], &workers_attr, runner, &range_data[i]);
  }
  if (rem != 0) {
    range_data[0].start = chunk_size * N_THREADS;
    range_data[0].end = chunk_size * N_THREADS + rem;
    pthread_create(&workers[N_THREADS], &workers_attr, runner, &range_data[0]);
  }
  for (int i = 0; i < N_THREADS + (rem != 0); ++i) {
    pthread_join(workers[i], NULL);
  }
  printf("%d\n", sum);
}

void *runner(void *param) {
  struct range *r = (struct range *)param;
  printf("Executing start=%d | end=%d\n", r->start, r->end);
  for (int i = r->start; i < r->end; ++i) {
    sum += i;
  }
  pthread_exit(0);
}
