#include <stdio.h>
#define N 10000
/* quick union for connectivity problem,better than quickfind but can degenerate
 * in single linked list => find in O(N), so in worst case can behave like
 * quickfind */
/* assume p,q < N */
int main() {
  int p, q;
  int id[N];
  for (size_t i = 0; i < N; ++i) {
    id[i] = i;
  }
  while (scanf("%d %d\n", &p, &q) == 2) {
    int i, j;
    for (i = p; i != id[i]; i = id[i])
      ;
    for (j = q; j != id[j]; j = id[j])
      ;
    if (i == j)
      continue;
    id[i] = j; /* connect i and j */
    printf("%d %d\n", p, q);
  }
}
