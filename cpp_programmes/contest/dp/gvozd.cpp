#include <iostream>
#include <vector>
#include <algorithm>

int inf = 1e4;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> nails(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nails[i];
    }
    
    std::sort(nails.begin(), nails.end());

    std::vector<int> dp(n, inf);
    dp[0] = 0;
    dp[1] = nails[1] - nails[0];
    dp[2] = nails[2] - nails[0];
    for (int i = 3; i < n; i++) {
        dp[i] = nails[i] - nails[i-1] + std::min(dp[i-1], dp[i-2]);
    }

    std::cout << dp[n-1];
}