#include <stdio.h>
#define N 10000
/* quick find for connectivity problem */
/* assume p,q < N */
int main() {
  int p, q;
  int id[N];
  for (size_t i = 0; i < N; ++i) {
    id[i] = i;
  }
  while (scanf("%d %d\n", &p, &q) == 2) {
    int t = id[p];
    if (t == id[q])
      continue;
    for (size_t i = 0; i < N; ++i) {
      if (t == id[i]) {
        id[i] = id[q];
      }
    }
    printf(" %d %d\n", p, q);
  }
}
