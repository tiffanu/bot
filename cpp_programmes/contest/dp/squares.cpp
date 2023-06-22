#include <iostream>
#include <vector>

using std::vector;

int main() {
    int n;
    std::cin >> n;

    vector < vector < int > > matr(n, vector < int > (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matr[i][j];
        }
    }

    vector < vector < int > > dp(n, vector < int > (n, 0));
    for (int i = 0; i < n; ++i) {
        dp[i][0] = matr[i][0];
        dp[0][i] = matr[0][i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (matr[i][j] == 1) {
                dp[i][j] = 1 + std::min(dp[i-1][j-1], std::min(dp[i][j-1], dp[i-1][j]));
            }
        }
    }

    int ans = matr[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            ans = (dp[i][j] > ans) ? dp[i][j] : ans;
        }
    }

    std::cout << ans << '\n';

}