#include <iostream>
#include <vector>

using std::vector;

long long peace(int n, int k, vector<vector<long long>>& dp) { 
    if (dp[n][k] == -1) {
        if (n < 0) return dp[n][k] = 0;
        if (n < k) return dp[n][k] = peace(n, n, dp);
        return dp[n][k] = peace(n, k-1, dp) + peace(n-k, k/2, dp); 
    }

    return dp[n][k];
}

int main() {
    int n;
    std::cin >> n;

    vector<vector<long long>> dp(n+1, vector<long long>(n+1, -1)); // dp[n][k] -- количество мирных множеств силы n на слагаемых <= k
    for (int i = 0; i <= n; i++) {
        dp[i][1] = 0;
        dp[0][i] = 1;
    }
    dp[1][1] = 1;

    std::cout << peace(n, n, dp);
}