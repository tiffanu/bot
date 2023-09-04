#include <bits/stdc++.h> 

using namespace std;

// Можно оформить в класс SegTree

int MAXN = 1e5;
vector<int> tree(4*MAXN, 0);

void build(const vector<int>& arr, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = arr[tl];
    } else {
        int tm = (tl + tr) >> 1;
        build(arr, 2*v, tl, tm);
        build(arr, 2*v+1, tm+1, tr);
        tree[v] = tree[2*v] + tree[2*v+1];
    }
}

void update(int v, int tl, int tr, int pos, int delta) {
    tree[v] += delta;
    if (tl == tr) return;

    int tm = (tl + tr) >> 1;
    if (pos <= tm) {
        update(2*v, tl, tm, pos, delta);
    } else {
        update(2*v+1, tm+1, tr, pos, delta);
    }
}

int getSum(int v, int tl, int tr, int l, int r) {
    if (tl == l && tr == r) {
        return tree[v];
    }

    int ans = 0;
    int tm = (tl + tr) >> 1;
    if (l <= tm) {
        ans += getSum(2*v, tl, tm, l, min(r, tm));
    }
    if (tm + 1 <= r) {
        ans += getSum(2*v+1, tm+1, tr, max(l, tm+1), r);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    for (int i = 1; i < n; i+=2) {
        numbers[i] = -numbers[i];
    }

    build(numbers, 1, 0, n-1);

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int command;
        cin >> command;

        if (command == 0) {  // ДО в 0-индексации, поэтому из всего в 1-инд вычитаем 1
            int i, j;
            cin >> i >> j;   // a[i] = j

            j = (i % 2 == 1 ? j : -j);

            update(1, 0, n-1, i-1, j - numbers[i-1]);
            numbers[i-1] += j - numbers[i-1];
        } else if (command == 1) { // \sum a_l - a_l+1 + ... +- a_r
            int l, r;
            cin >> l >> r;

            int ans = ((l % 2 == 1) ? 1 : -1) * getSum(1, 0, n-1, l-1, r-1);
            cout << ans << '\n';
        }
    }    
}