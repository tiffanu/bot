#include <iostream>

int main() {
  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int j = 0; j < n; j++) {
      int el;
      std::cin >> el;
      sum += (i==j) ? 2*el : el;
    }
    if (sum % 2 != 0) {
      std::cout << "NO\n";
      return 0;
    }
  }

  std::cout << "YES\n";
}