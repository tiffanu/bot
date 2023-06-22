#include <iostream>
#include <vector>
#include <stack>

using std::vector;

vector<vector<int>> g(100000);
bool is_acyclic = false;
int cycle_start = -1;

vector<int> color(100000, 0); // 0 - w, 1 - g, 2 - b

vector<int> parent(100000);

void dfs(int v, int p = -1) {
  if (color[v] == 2) return;

  color[v] = 1;
  parent[v] = p;

  for (int to : g[v]) {
    if (color[to] == 0) {
      dfs(to, v);
    } else if (color[to] == 1) {
      is_acyclic = true;
      cycle_start = to;
      parent[to] = v;
    }
  }

  color[v] = 2;
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
    std::cout << "YES\n";
    std::stack<int> ans;

    int v = cycle_start;
    do {
      ans.push(v);
      v = parent[v];
    } while (v != cycle_start);

    while (!ans.empty()) {
      std::cout << 1 + ans.top() << ' ';
      ans.pop();
    }

  } else {
    std::cout << "NO\n";
  }

}