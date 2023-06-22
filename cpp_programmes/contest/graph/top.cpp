#include <iostream>
#include <vector>
#include <stack>

using std::vector;

std::stack<int> ans;

vector<vector<int>> g(100000);
bool is_acyclic = false;

vector<int> color(100000, 0); // 0 - w, 1 - g, 2 - b

void dfs(int v) {
  if (color[v] == 2) return;

  color[v] = 1;

  for (int to : g[v]) {
    if (color[to] == 0) dfs(to);
    else if (color[to] == 1) is_acyclic = true;
  }

  color[v] = 2;
  ans.push(v);
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int from, to;
    std::cin >> from >> to;

    g[from-1].push_back(to-1);
  }

  for (int v = 0; v < n; v++) {
    dfs(v);
  }

  if (is_acyclic) {
    std::cout << -1 << '\n';
    return 0;
  }

  while (!ans.empty()) {
    std::cout << 1 + ans.top() << ' ';
    ans.pop();
  }
  
}