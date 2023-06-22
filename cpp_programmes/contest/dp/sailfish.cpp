#include <stdio.h>
#include <vector>

using std::vector;

int min3(int a, int b, int c) {
  return std::min(a, std::min(b, c));
}
int min4(int a, int b, int c, int d) {
  return std::min(a, std::min(b, std::min(c, d)));
}

int time(int i, vector<vector<int>>& queue, vector<int>& cache, int n) {
  if (!cache[i]) {
    cache[i] = min3(queue[i][0] + time(i+1, queue, cache, n), queue[i][1] + time(i+2, queue, cache, n), queue[i][2] + time(i+3, queue, cache, n));
  }
  return cache[i];
}

int main() {
  int n;
  scanf("%d", &n);

  vector<vector<int>> queue(n, vector<int>(3));
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &queue[i][0], &queue[i][1], &queue[i][2]);
  }

  vector<int> cache(n, 0);
  cache[n-1] = queue[n-1][0];
  if (n >= 2) cache[n-2] = std::min(queue[n-2][1], queue[n-2][0] + queue[n-1][0]);
  if (n >= 3) cache[n-3] = min4(queue[n-3][2], queue[n-3][1] + queue[n-1][0], queue[n-3][0] + queue[n-2][1], queue[n-3][0] + queue[n-2][0] + queue[n-1][0]);

  printf("%d", time(0, queue, cache, n));
}