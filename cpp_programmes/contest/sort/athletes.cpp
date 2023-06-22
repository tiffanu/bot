#include <stdio.h>
#include <algorithm>

struct Athlet {
  long long mass;
  long long str;
};

bool ath_cmp(const Athlet& lhs, const Athlet& rhs) {
  if (lhs.mass == rhs.mass) {
    return (lhs.str < rhs.str);
  }
  return (lhs.mass < rhs.mass);
}

int main() {
  size_t n;
  scanf("%zu", &n);

  Athlet* athlets = new Athlet[n];
  for (size_t i = 0; i < n; i++) {
    scanf("%lld %lld", &athlets[i].mass, &athlets[i].str);
  }

  std::sort(athlets, athlets+n, ath_cmp);

  int count = 1;
  long long curr_mass = athlets[0].mass;
  for (size_t i = 1; i < n; i++) {
    if (athlets[i].str >= curr_mass) {
      ++count;
      curr_mass += athlets[i].mass;
    }
  }

  printf("%d", count);

  delete [] athlets;
}