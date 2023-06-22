#include <stdio.h>
#include <vector>

void merge(std::vector<int>& b, std::vector<int>& c, std::vector<int>& a, long long& inv) {
    int i = 0, j = 0, p = 0;
    while (i < b.size() && j < c.size()) {
        if (b[i] <= c[j]) {
            a[p++] = b[i++];
            inv += j;
        } else a[p++] = c[j++];
    }
    while (i < b.size()) {
        a[p++] = b[i++];
        inv += c.size();
    }
    while (j < c.size()) a[p++] = c[j++];
}

void mergesort(std::vector<int>& a, long long& inv) {
    if (a.size() == 1) return;

    std::vector<int> b, c;
    for (int i = 0; i < a.size()/2; i++) {
        b.push_back(a[i]);
    }
    for (int i = 0; i < (a.size() + 1)/2; i++) {
        c.push_back(a[i + a.size()/2]);
    }

    mergesort(b, inv);
    mergesort(c, inv);

    merge(b, c, a, inv);
}

int main() {
    size_t n;
    scanf("%zu", &n);

    long long inv = 0;

    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        int el;
        scanf("%d", &el);
        arr.push_back(el);
    }

    mergesort(arr, inv);

    printf("%lld", inv);  
}