#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
const int inf = 1e6 + 1;

int main() {
    int n;
    std::cin >> n;

    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i];
    }
    std::sort(values.begin(), values.end());

    int s;
    std::cin >> s;

    vector<int> dp(s+1, inf);
    dp[0] = 0;
    
    for (int i = 1; i <= s; i++) {
        for (int j = 0; j < n && i >= values[j]; j++) {
            int prev = 1 + dp[i - values[j]];
            dp[i] = (dp[i] > prev) ? prev : dp[i];
        }
    }

    if (dp[s] == inf) {
        std::cout << -1 << '\n';
    } else { 
        std::cout << dp[s] << '\n';
        while (s > 0) {
            for (int i = 0; i < n && s >= values[i]; i++) {
                if (dp[s] == 1 + dp[s - values[i]]) {
                    std::cout << values[i] << ' ';
                    s -= values[i];
                }
            }
        }
    }

}