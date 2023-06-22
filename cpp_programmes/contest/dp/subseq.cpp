#include <iostream>
#include <vector>

using std::vector;

int inf = (1 << 31) - 1;

int main() { 
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];     
    }
    a.push_back(-inf);

    vector<int> prev(n, -1); // p[i] - индекс элемента на котором кончается нвп длины i


    vector<int> dp(n, n); // vector of idx
    for (int i = 0; i < n; i++) {
        int l = -1, r = n-1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (a[dp[mid]] < a[i]) {
                r = mid;
            } else {
                l = mid;
            }
        }
        dp[r] = i;
        if (r != 0) {
            prev[i] = dp[r-1];
        }
    }

    int l = 0, r = n;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (dp[mid] == n) {
            r = mid;
        } else {
            l = mid;
        }
    }

    int max_dp = dp[l], max_i = l+1;
    std::cout << max_i << '\n';
    
    vector<int> ans;
    ans.push_back(max_dp);

    int p = prev[max_dp];
    while (p != -1) {
        ans.push_back(p);
        p = prev[p];
    }

    for (int i = ans.size(); i > 0; i--) {
        std::cout << 1 + ans[i-1] << ' ';
    }
}