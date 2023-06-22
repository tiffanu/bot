#include <iostream>
#include <vector>

using std::vector;

int decompositions(int n, int k, vector<vector<int>>& dp) { 
    if (!dp[n][k]) {
        if (n < 0) return dp[n][k] = 0;
        if (k == 1 || n == 0) return dp[n][k] = 1;
        if (n < k) return dp[n][k] = decompositions(n, n, dp);
        return dp[n][k] = decompositions(n, k-1, dp) + decompositions(n-k, k, dp); 
    }

    return dp[n][k];
}

int main() {
    int n;
    std::cin >> n;

    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    std::cout << decompositions(n, n, dp);
}