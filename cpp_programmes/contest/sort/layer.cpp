#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct slice {
    int left;
    int right;

    int len() const {
        return right - left;
    }
};

bool operator<(const slice& first, const slice& second) {
    if (first.left == second.left) {
        return (first.len() < second.len());
    }
    return (first.left < second.left);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<slice> layer(n);

    for (int i = 0; i < n; ++i) {
        cin >> layer[i].left >> layer[i].right;
    }

    std::sort(layer.begin(), layer.end());

    int ans = layer[0].len();
    int max_r = layer[0].right, curr_l = layer[0].left;
    for (int i = 1; i < n; ++i) {
        if (layer[i].left >= max_r) {
            ans += layer[i].len();

            max_r = layer[i].right;
            curr_l = layer[i].left;
        } else if (layer[i].right >= max_r) {
            layer[i].left = std::max(layer[i].left, curr_l);
            ans -= max_r - layer[i].left;
            ans += layer[i].right - max_r;

            curr_l = max_r;
            max_r = layer[i].right;
        } else if (layer[i].right < max_r) {
            layer[i].left = std::max(layer[i].left, curr_l);
            if (layer[i].len() > 0) {
                ans -= layer[i].len();
            }

            curr_l = std::max(layer[i].right, curr_l);
        }
    }

    cout << ans << '\n';
}