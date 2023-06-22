#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

const int inf = 1e9;

struct edge {
    int to;
    int w;
};

vector<vector<edge>> g(1024);
vector<bool> used(1024, false);

int main() {
    int n, m;
    std::cin >> n >> m;

    int ans = 0;

    for (int i = 0; i < m; ++i) {
        int from, to, w;
        std::cin >> from >> to >> w;

        g[from].push_back({to, w});
        g[to].push_back({from, w});
    }

    vector<int> dist(n, inf);

    dist[0] = 0;
    for (int i = 0; i < n; ++i) {
        int min = inf, u = 0;
        for (int v = 0; v < n; ++v) {
            if (dist[v] < min && !used[v]) {
                u = v;
                min = dist[v];
            }
        }
        ans += dist[u];

        for (edge e : g[u]) {
            dist[e.to] = std::min(dist[e.to], e.w);
        }

        dist[u] = inf + 1;
        used[u] = true;
    }
    
    std::cout << ans << '\n';

    return 0;
}
