/* here several stuff: sharing ptrs in multithreaded prog, callbacks and oop in
 * C  */

/* SHARING PTRS, dumb example(matrix prod) */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t mutex_sum;

typedef struct {
  double *vector_a;
  double *vector_b;
  double sum; /* hold dot product */
  int length; /* portion of vector thread will process != entire len of V */
} Vector_info;

typedef struct {
  Vector_info *info;
  int beg_index;
} Product;

void *dot_product(void *prod) {
  Product *product = (Product *)prod;
  Vector_info *vec_info = product->info; /* vec info to modify */

  int start = product->beg_index;

  int end = start + vec_info->length;
  double total = 0;

  for (int i = start; i < end; ++i) {
    total += (vec_info->vector_a[i] * vec_info->vector_b[i]);
  }
  pthread_mutex_lock(&mutex_sum);
  vec_info->sum += total;
  pthread_mutex_unlock(&mutex_sum);
  pthread_exit(NULL);
}

#define N_THREADS 4
void test() {
  Vector_info vec_info;
  double vectorA[] = {1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
  double vectorB[] = {1.0, 2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
                      9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  vec_info.vector_a = vectorA;
  vec_info.vector_b = vectorB;
  vec_info.length = 4;

  pthread_t threads[N_THREADS];
  pthread_attr_t attr;

  pthread_mutex_init(&mutex_sum, NULL);
  pthread_attr_init(&attr);

  for (size_t i = 0; i < N_THREADS; ++i) {
    Product *prod = (Product *)malloc(sizeof(Product));
    prod->info = &vec_info;
    prod->beg_index = N_THREADS * i;
    if (pthread_create(&threads[i], &attr, dot_product, prod)) {
      // return EXIT_FAILURE;
    }
  }
  for (size_t i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }
  pthread_mutex_destroy(&mutex_sum);
  printf("Dot Product sum: %lf\n", vec_info.sum);
  // return EXIT_SUCCESS;
}

/* now callbacks,namely when an event in one thread result in invocation of
 * function in new thread. */
/* let's do an example with factorial! */
typedef struct _factorial_data {
  size_t number;
  size_t result;
  void (*callback)(struct _factorial_data *);
} Factorial_data;

void *factorial(void *args) {
  Factorial_data *fact_data = (Factorial_data *)args;

  int number = fact_data->number;
  void (*callback)(Factorial_data *) = fact_data->callback;

  size_t num = 1;
  for (size_t i = 1; i <= number; ++i) {
    num *= i;
  }
  printf("%zu\n", num);
  fact_data->result = num;
  callback(fact_data);
  pthread_exit(NULL);
}
void start_thread(Factorial_data *data) {
  pthread_t t_id;
  pthread_create(&t_id, NULL, factorial, data);
}
void callback_foo(Factorial_data *data) {
  printf("Fact(%zu)=%zu\n", data->number, data->result);
}
int main() {
  Factorial_data d;
  d.number = 5;
  d.callback = callback_foo;
  start_thread(&d);
  sleep(2000);/* means that meanwhile can execute other stuff */
}

/* now oop in C, pretty trivial, no time for that now */
