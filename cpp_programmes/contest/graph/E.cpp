#include <iostream>
#include <vector>
#include <map>

int main() {
  int n;
  std::cin >> n;

  std::map<int, std::vector<int>> ans;
  for (int i = 0; i < n; i++) {
    int from, to, weight;
    std::cin >> from >> to >> weight;

    ans[from].push_back(0);
    ans[from].push_back(0);
    
    ++ans[from][0];
    ans[from][1] += weight;
  }

  for (auto& [key, value] : ans) {
    std::cout << key << ' ' << value[0] << ' ' << value[1] << '\n';
  }
}
