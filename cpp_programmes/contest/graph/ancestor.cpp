#include <iostream>
#include <vector>

using std::vector;

vector<vector<int>> g(100000);

vector<long long> tin(100000), tout(100000);
long long timer = 0;

vector<int> color(100000, 0); // 0 - w, 1 - g, 2 - b

void dfs(int v) {
  if (color[v] == 2) return;

  color[v] = 1;
  tin[v] = timer++;

  for (int to : g[v]) {
    if (color[to] != 0) continue;
    dfs(to);
  }

  color[v] = 2;
  tout[v] = timer++;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  int parent;
  for (int i = 0; i < n; i++) {
    std::cin >> parent;

    g[parent].push_back(i+1);
  }

  dfs(0);

  int m;
  std::cin >> m;

  int child;
  for (int i = 0; i < m; i++) {
    std::cin >> parent >> child;

    std::cout << ((tin[child] >= tin[parent]) && (tout[child] <= tout[parent])) << '\n';
  }
}