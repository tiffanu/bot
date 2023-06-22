#include <iostream>
#include <vector>

using std::vector;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    vector<int> dp(n, 1);
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (a[j] % a[i] == 0) {
                dp[j] = std::max(1 + dp[i], dp[j]);
            }
        }
    }

    int max = 0;
    for (int i = 0; i < n; i++) {
        max = (dp[i] > max) ? dp[i] : max;
    }

    std::cout << max << '\n';
}