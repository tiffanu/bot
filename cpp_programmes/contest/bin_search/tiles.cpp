#include <iostream>
#include <algorithm>

using namespace std;

bool min_length(int64_t m, int w, int d, int n){
  return (m / w) * (m / d) >= n;
}

int main(){
  int w, d, n;
  cin >> w >> d >> n;

  int64_t l = 0, r = static_cast<int64_t>(n)*max(w, d), mid;
  while (r - l > 1) {
    mid = (l + r) / 2;
    if (min_length(mid, w, d, n)) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << r;
}