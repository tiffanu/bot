#include <iostream>
#include <vector>

bool bin_search(int k, std::vector<int>& a, std::vector<int>& b) {           // проверка на убывание/возрастание
  int max = (a[k] > b[k]) ? a[k] : b[k];
  --k;
  int prev_max = (a[k] > b[k]) ? a[k] : b[k];

  while (max == prev_max) {
    --k;
    prev_max = (a[k] > b[k]) ? a[k] : b[k];
  }
  return (max > prev_max);
} // 1 -- возр, 0 -- убывает

int main() {
  size_t n, m, l;
  scanf("%zu %zu %zu", &n, &m, &l);

  std::vector<std::vector<int>> incr;
  std::vector<std::vector<int>> decr;

  for (int i = 0; i < n; i++) {
    std::vector<int> a(l+2);                // создаём 2 фиктивных элемента для бинарного поиска 
    a[0] = 0;
    for (int j = 1; j <= l; j++) {
      scanf("%d", &a[j]);
    }
    a[l+1] = 100000;
    incr.push_back(a);
  }

  for (int i = 0; i < m; i++) {
    std::vector<int> b(l+2);
    b[0] = 100000;
    for (int j = 1; j <= l; j++) {
      scanf("%d", &b[j]);
    }
    b[l+1] = 0;
    decr.push_back(b);
  }

  size_t q;
  scanf("%zu", &q);

  for (int iter = 0; iter < q; iter++) {
    int i, j;
    scanf("%d %d", &i, &j);

    int left = 0, right = l;
    while (right - left > 1) {
      int mid = (left + right)/2;
      if (bin_search(mid, incr[i-1], decr[j-1])) {
        right = mid;
      } else {
        left = mid;
      }
    }
    int max_l = (incr[i-1][left] > decr[j-1][left]) ? incr[i-1][left] : decr[j-1][left];
    int max_r = (incr[i-1][right] > decr[j-1][right]) ? incr[i-1][right] : decr[j-1][right];
    (max_l < max_r) ? printf("%d\n", left) : printf("%d\n", right);
  }
}