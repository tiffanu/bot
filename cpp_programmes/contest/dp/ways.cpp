#include <stdio.h>
#include <stdlib.h>

long long int ways(int row, int col, int num_cols, long long int* cache) {
  if (cache[col + row*num_cols]) return cache[col + row*num_cols];
  if (row*col == 0) return cache[col + row*num_cols] = 1;
  return cache[col + row*num_cols] = ways(row, col-1, num_cols, cache) + ways(row-1, col, num_cols, cache);
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  long long int* cache = (long long int *)calloc((n+1)*(m+1), sizeof(long long int));

  printf("%lld", ways(n, m, m+1, cache));
}