#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct edge {
    int to;
    int num;
};

vector<vector<edge>> g(20000);

int timer = 0;
vector<int> tin(20000);
vector<int> fup(20000);           // from E-maxx

vector<int> parent(20000);
vector<bool> color(20000, false); // false -- unused, true -- used

vector<int> ans;

void dfs(int v, int p = -1) {
    if (color[v] != 0) return;

    tin[v] = fup[v] = timer++;
    color[v] = true;
    parent[v] = p;

    for (edge e : g[v]) {
        if (p == e.to) continue;

        if (color[e.to] == true) {

            fup[v] = std::min(fup[v], tin[e.to]);
        
        } else {

            dfs(e.to, v);
            fup[v] = std::min(fup[v], fup[e.to]);
        }

        if (fup[e.to] > tin[v]) ans.push_back(e.num+1);

    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;

        g[from-1].push_back({to-1, i});
        g[to-1].push_back({from-1, i});
    }

    for (int v = 0; v < n; v++) {
        dfs(v);
    }

    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';
    for (int el : ans) std::cout << el << '\n';
}