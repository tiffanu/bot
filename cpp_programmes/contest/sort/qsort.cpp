#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;                    // написать QuickSelect через медиану медиан

int QuickSelect(vector<int>& arr, int l, int r) {
    if (l != r ) {
        std::swap(arr[l + (r - l)/2], arr[r]);
    }

    int x = arr[r];
    int i = l - 1;

    for (int j = l; j <= r; j++) {
        if (arr[j] <= x)
            std::swap(arr[++i],arr[j]);
    }

    return i;
}

void QuickSort(vector<int>& arr, int l,  int r) {
    if (arr.size() == 1) {
        return;
    }

    int pivot = QuickSelect(arr, l, r);

    QuickSort(arr, l, pivot);
    QuickSort(arr, pivot, r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::sort(arr.begin(), arr.end());

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
}