#include <bits/stdc++.h> 

using namespace std;


int MAXN = 1e5;
const bool IsMin = true, IsMax = false;


template <bool IsMin>
class SegTree {
private:

    vector<int> tree;
    int _default = (IsMin ? 2e5 : -2e5);

    void vert_update(int v) {
        if (IsMin) {
            tree[v] = min(tree[2*v], tree[2*v+1]);
        } else {
            tree[v] = max(tree[2*v], tree[2*v+1]);
        }
    }

public:

    SegTree(int n) {
        tree = vector<int>(4*n, _default);
    }


    void build(const vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) >> 1;
            build(arr, 2*v, tl, tm);
            build(arr, 2*v+1, tm+1, tr);
            vert_update(v);
        }
    }

    void update(int v, int tl, int tr, int pos, int new_value) {
        if (tl == tr) {
            tree[v] = new_value;
            return;
        }

        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            update(2*v, tl, tm, pos, new_value);
        } else {
            update(2*v+1, tm+1, tr, pos, new_value);
        }
        vert_update(v);
    }

    int get(int v, int tl, int tr, int l, int r) const {
        if (tl == l && tr == r) {
            return tree[v];
        }

        int ans = _default;
        int tm = (tl + tr) >> 1;
        if (l <= tm) {
            if (IsMin) {
                ans = min(ans, get(2*v, tl, tm, l, min(r, tm)));
            } else {
                ans = max(ans, get(2*v, tl, tm, l, min(r, tm)));
            }
        }
        if (tm + 1 <= r) {
            if (IsMin) {
                ans = min(ans, get(2*v+1, tm+1, tr, max(l, tm+1), r));
            } else {
                ans = max(ans, get(2*v+1, tm+1, tr, max(l, tm+1), r));
            }        }
        return ans;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    
    SegTree<IsMin> tree_min(n);
    SegTree<IsMax> tree_max(n);

    tree_min.build(numbers, 1, 0, n-1);
    tree_max.build(numbers, 1, 0, n-1);


    while (m--) {
        int command, i, x;
        cin >> command >> i >> x;

        if (command == 0) {
            tree_max.update(1, 0, n-1, i-1, x);
            tree_min.update(1, 0, n-1, i-1, x);
            numbers[i-1] = x;
        } else if (command == 1) {

        }





        // int x, y;
        // cin >> x >> y;

        // if (x > 0) {  // ДО в 0-индексации, поэтому из всего в 1-инд вычитаем 1
        //     int ans;
        //     ans = tree_max.get(1, 0, n-1, x-1, y-1) - tree_min.get(1, 0, MAXN-1, x-1, y-1);
        //     cout << ans << '\n';
        // } else if (x < 0) {
        //     x = -x;
        //     tree_max.update(1, 0, n-1, x-1, y);
        //     tree_min.update(1, 0, n-1, x-1, y);
        //     numbers[x-1] = y;
        // }
    }    
}