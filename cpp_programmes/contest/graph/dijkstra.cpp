#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

const int inf = 1e9;

struct edge {
    int to;
    int w;
};

vector<vector<edge>> g(100);
vector<bool> used(100, false);

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int from, to, w;
        std::cin >> from >> to >> w;

        g[from].push_back({to, w});
        g[to].push_back({from, w});
    }

    int start;
    std::cin >> start;

    vector<int> dist(n, inf);

    dist[start] = 0;
    for (int i = 0; i < n; ++i) {
        int min = inf+1, u = 0;
        for (int v = 0; v < n; ++v) {       // u - неиспользованная вершина с минимальным расстоянием
            if (dist[v] < min && !used[v]) {
                u = v;
                min = dist[v];
            }
        }

        for (edge& e : g[u]) {
            dist[e.to] = std::min(dist[e.to], dist[u] + e.w);
        }

        used[u] = true;
    }

    for (int d : dist) std::cout << d << ' ';
}