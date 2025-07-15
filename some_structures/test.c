#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void safer_free(void **pp) {
  if (pp != NULL && *pp != NULL) {
    free(*pp);
    *pp = NULL;
  }
}
#define safe_free(p) safer_free((void **)&(p))

#define RAII_VARIABLE(vartype, varname, initval, dtor)                         \
  void _dtor_##varname(vartype *v) { dtor(*v); }                               \
  vartype varname __attribute__((cleanup(_dtor_##varname))) = (initval)

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
  init_ops();
  printf("%d\n", eval('+', 10, 240));
}
