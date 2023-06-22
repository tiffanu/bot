#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct slice {
    int left;
    int right;
};

int main() {
    int n;
    std::cin >> n;

    vector<slice> layer(n);

    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> layer[i].left >> layer[i].right;
    }

    std::sort(layer.begin(), layer.end());

    for (int i = 0; i < n; ++i) {
        
    }
}