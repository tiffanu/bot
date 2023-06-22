#include <iostream>
#include <vector>

bool is_killed(long long hits, std::vector<int>& hp, int p, int q) {
  long long extra_hits = 0;

  for (size_t i = 0; i < hp.size(); i++) {
    if (hp[i] > q*hits) {
      extra_hits += (hp[i] - q*hits - 1)/(p - q) + 1;
    }
  }

  return (extra_hits <= hits);
}

int main() {
  int n, p, q;
  scanf("%d %d %d", &n, &p, &q);

  long long l_hits, r_hits; // for bin_s
  int max = 0, min = 1e9;
  long long sum = 0; 

  std::vector<int> hp(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &hp[i]);
    sum += hp[i];
    max = (hp[i] > max) ? hp[i] : max;
    min = (hp[i] < min) ? hp[i] : min;
  }

  r_hits = max/q + 1;
  l_hits = min/p;

  if (p == q) {
    printf("%d", (max - 1 + p)/p);
    return 0;
  }

  while (r_hits - l_hits > 1) {
    long long mid = (l_hits + r_hits)/2;
    if (is_killed(mid, hp, p, q)) {
      r_hits = mid;
    } else {
      l_hits = mid;
    }
  }

  printf("%lld", r_hits);

}