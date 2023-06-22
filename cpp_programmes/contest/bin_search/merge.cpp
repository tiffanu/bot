#include <stdio.h>


int main(){
  size_t n;
  scanf("%zu", &n);

  long long total_sum = 0ll;
  long long *w = new long long[n];

  for (size_t i = 0; i < n; ++i){
    scanf("%lld", w+i);
  }

  long long tmp;
  scanf("%lld", &tmp);

  size_t i = 0, j = 0;
  while (i < n && j < n){
    if (w[i] < tmp){
      total_sum += w[i] * ((i+j) % 2 == 0);
      i++;
    } else {
      total_sum += tmp * ((i+j) % 2 == 0);
      j++;
      if (j != n) scanf("%lld", &tmp);
    }
  }

  while (i < n){
    total_sum += w[i] * ((i+j) % 2 == 0);
    i++;
  }

  while (j < n){
      total_sum += tmp * ((i+j) % 2 == 0);
      j++;
      if (j != n) scanf("%lld", &tmp);
    }
  
  printf("%lld", total_sum % 1000000000);

  delete [] w;
}