#include "stack.h"
#include "assert.h"
#include "mem.h"
#include <stddef.h>

/*
 Checked runtime errors:
 - passing null Stack_T to any function in this interface
 - passing null ptr to Stack_Free
 - passing empty stack to Stack_pop
 Unchecked runtime errors:
    void ptr stuff, cant pass function ptr, cant make certain conversion.
 Exceptions:
    None
 */

struct stack_T {
  int count;
  struct elem {
    void *x;
    struct elem *link;
  } *head;
};
typedef struct stack_T *Stack_T;

/* Stack_new allocates and init a new T */
Stack_T stack_new(void) {
  Stack_T stk;

  NEW(stk);
  stk->count = 0;
  stk->head = NULL;
  return stk;
}

int Stack_empty(Stack_T stk) {
  assert(stk);
  return stk->count == 0;
}

void Stack_push(Stack_T stk, void *x) {
  assert(stk);

  struct elem *t;
  NEW(t);
  t->x = x;
  t->link = stk->head;
  stk->head = t;
  stk->count++;
}
void *Stack_pop(Stack_T stk) {
  assert(stk);
  assert(stk->count > 0);

  void *x;
  struct elem *t = stk->head;
  stk->head = t->link;
  stk->count--;
  x = t->x;
  FREE(t);
  return x;
}

void Stack_free(Stack_T *stk) {
  assert(stk && *stk);

  struct elem *t, *u;
  for (t = (*stk)->head; t; t = u) {
    u = t->link;
    FREE(t);
  }
  FREE(*stk);

}
