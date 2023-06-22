#include <stdio.h>

size_t findK(long long *p, long long m, size_t n){ // 1 2 3 4 5 6 7 8 9 10
  size_t min_k = 1;
  long long sum_pages = 0;
  for (size_t i = 0; i < n; i++){ 
    sum_pages += p[i];
    if (sum_pages > m){
      min_k++;
      i--;
      sum_pages = 0;
    }
  }

  return min_k;
}

int main(){
  size_t k, n;
  scanf("%zu %zu", &k, &n);

  long long max = 0;
  long long *pages = new long long[n];
  
  for (size_t i = 0; i < n; i++){
    scanf("%lld", &pages[i]);
    if (max < pages[i]) max = pages[i];
  }

  long long l = max - 1, r = 10000ll * n, mid; 
  while (r - l > 1){
    mid = (l + r) / 2;
    if (findK(pages, mid, n) > k){
      l = mid;
    } else {
      r = mid;
    }
  }

  printf("%lld", r);

  delete [] pages;
}