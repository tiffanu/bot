#include <iostream>
#include <vector>
#include <set>

using std::vector;

vector<vector<int>> g(100000);
vector<int> tower_comp(100000, 0);

void dfs(int v, int num) {
  if (tower_comp[v] != 0) return;

  tower_comp[v] = num;

  for (int to : g[v]) {
    dfs(to, num);
  }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    std::set<int> vertex;

    if (n-1 > m) {
        std::cout << -1;
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;

        g[from].push_back(to);
        g[to].push_back(from);

        vertex.insert(from);
        vertex.insert(to);
    }

    int s = 1;
    for (int v : vertex) {
        if (tower_comp[v] == 0) {
            dfs(v, s);
            ++s;
        }
    }
    // получили распределение вершин по компонентам связности

    int ans = 0;
    for (int v : vertex) {
        ans = (tower_comp[v] > ans) ? tower_comp[v] : ans;
    }
    std::cout << n - vertex.size() + ans - 1 << '\n';
}