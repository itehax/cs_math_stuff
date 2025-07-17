#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void safer_free(void **pp) {
  if (pp != NULL && *pp != NULL) {
    free(*pp);
    *pp = NULL;
  }
  puts("deallocated!");
}
#define FREE(p) safer_free((void **)&(p))

#define RAII_VARIABLE(vartype, varname, dtor)                                  \
  inline void _dtor_##varname(vartype *v) { dtor(*v); }                        \
  vartype varname __attribute__((cleanup(_dtor_##varname)))

#define KEEP_ALIVE(vartype,varname) //here i wanto set \

#define MANY(T, Q) (T *)malloc(sizeof(T) * (Q))
#define NEW(T) MANY(T, 1)

int add(int x, int y) { return x + y; }
int sub(int x, int y) { return x - y; }

/* otherwise int(*op[128])(int,int) = {NULL}; */
typedef int (*Op)(int, int);
Op ops[128] = {NULL};
void init_ops() {
  ops['+'] = add;
  ops['-'] = sub;
}
int eval(char opcode, int x, int y) {
  Op op = ops[opcode];
  return op(x, y);
}

int main() {
  RAII_VARIABLE(int *, test, FREE) = MANY(int, 5);
  printf("%p\n", test);
  RAII_VARIABLE(int *, testt, FREE) = NEW(int);
  printf("%p\n", testt);
}
