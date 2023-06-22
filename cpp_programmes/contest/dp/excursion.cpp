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
}
