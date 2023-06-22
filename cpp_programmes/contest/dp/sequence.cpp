#include <iostream>
#include <vector>

int sequence(int n, std::vector<int>& dp) {
  if (!dp[n]) {
    dp[n] = sequence(n-1, dp) + sequence(n-2, dp);
  }

  return dp[n];
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> dp(n+1, 0);
  dp[0] = 1;
  dp[1] = 2;

  std::cout << sequence(n, dp);
}