#include <stdio.h>


int main(){
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  long long *m = new long long[n];
  for (size_t i = 0; i < n; ++i){
    scanf("%lld", m+i);
  }

  for (size_t i = n - 1; i > 0; --i){
    m[i] -= m[i-1];
  }

  long long x;
  size_t l, r;
  for (size_t i = 0; i < q; ++i){
    scanf("%zu %zu %lld", &l, &r, &x);
    m[l] += x;
    if (r+1 < n){
      m[r+1] -= x;
    }
  }

  printf("%lld ", m[0]);
  for (size_t i = 1; i < n; ++i){
    m[i] += m[i-1];
    printf("%lld ", m[i]);
  }

  delete [] m;
}