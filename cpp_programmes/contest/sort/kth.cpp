#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

int partition(vector<int>& mas, int l, int r) {
    if (l!=r)
        swap(mas[l + (r - l)/2], mas[r]);
    int x = mas[r];
    int i = l-1;
    for (int j = l; j <= r; j++) {
        if (mas[j] <= x)
            swap(mas[++i],mas[j]);
    }
    return i;
}

int kth(vector<int>& mas, int n) {
  int l = 0, r = mas.size() - 1;
  for(;;) {
    int pos = partition(mas,l,r);
    if (pos < n)
      l = pos + 1;
    else if (pos > n)
      r = pos - 1;
    else return mas[n];
  }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cout << kth(arr, k);
}