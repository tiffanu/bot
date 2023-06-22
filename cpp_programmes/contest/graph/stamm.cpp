#include <iostream>
#include <vector>

using std::vector;

vector<vector<int>> g(20000);

vector<int> stamm(20000, 0);

void dfs(int v, int virus) {
  if (stamm[v] != 0) return;

  stamm[v] = virus;

  for (int to : g[v]) {
    if (stamm[to] != 0) continue;
    dfs(to, virus);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  std::cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int from, to;
    std::cin >> from >> to;

    g[from].push_back(to);
    g[to].push_back(from);
  }

  int s = 1, i = 1;
  while (i <= n) {
    if (stamm[i] == 0) {
      dfs(i, s);
      ++s;
    }
    ++i;
  }

  std::cout << s-1 << '\n';
  for (int i = 1; i <= n; i++) {
    std::cout << stamm[i] << ' ';
  }
}