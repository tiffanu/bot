// массив не отсортирован
#include <stdio.h>
#include <stdlib.h>

int compare(const void *lhs, const void *rhs){
  return *(int*)lhs - *(int*)rhs;
}

int main(){
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  long long *nums = new long long[n];
  for (size_t i = 0; i < n; i++){
    scanf("%lld", &nums[i]);
  }

  qsort(nums, n, sizeof(long long), compare);

  long long p;
  for (size_t k = 0; k < m; k++){
    scanf("%lld", &p);
    int i = 0, j = n-1;
    while (i < j){
      if (nums[i] + nums[j] > p) j--;
      else if (nums[i] + nums[j] < p) i++;
      else {
        printf("%lld %lld\n", nums[i], nums[j]);
        break;
      }
    }
    if (i == j) printf("Not found\n");
  }

  delete [] nums;
}