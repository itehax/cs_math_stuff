/* weighted quick union: just like quick union but i keep track |V| of each tree
 * an link the smaller to the bigger. */
#include <stdio.h>
#define N 10000
int main() {
  int p, q;
  int id[N];
  int n_nodes[N];
  for (size_t i = 0; i < N; ++i) {
    id[i] = i;
    n_nodes[i] = 1;
  }
  while (scanf("%d %d\n", &p, &q) == 2) {
    int i, j;
    for (i = p; i != id[i]; i = id[i])
      ;
    for (j = q; j != id[j]; j = id[j])
      ;
    if (i == j) {
      continue;
    }
    if (n_nodes[i] > n_nodes[j]) {
      id[j] = i; /* connect j to i */
      n_nodes[i] += n_nodes[j];
    } else {
      id[i] = j; /* connect i to j */
      n_nodes[j] += n_nodes[i];
    }
    printf("%d %d\n", p, q);
  }
}
