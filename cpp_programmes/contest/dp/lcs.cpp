#include <iostream>
#include <vector>

using std::vector;

int main() {
    int n;
    std::cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int m;
    std::cin >> m;

    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[0][0] = (a[0] == b[0]);
    for (int j = 1; j < m; j++) {
        dp[0][j] = (a[0] == b[j]) ? 1 : dp[0][j-1];
    }

    for (int i = 1; i < n; i++) {
        dp[i][0] = (a[i] == b[0]) ? 1 : dp[i-1][0];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (a[i] == b[j]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            dp[i][j] = std::max(dp[i][j], std::max(dp[i-1][j], dp[i][j-1]));
        }
    }

    std::cout << dp[n-1][m-1] << '\n';

}