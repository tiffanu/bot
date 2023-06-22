#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<vector<int>> g(10000);
vector<vector<int>> rev_g(10000);

vector<int> order;

vector<int> color(10000, 0); // 0 - w, 1 - g, 2 - b

void dfs(int v) {
    if (color[v] == 2) return;

    color[v] = 1;

    for (int to : g[v]) {
        if (color[to] != 0) continue;
        dfs(to);
    }

    color[v] = 2;
    order.push_back(v);
}

int outer = 0;
vector<bool> visited_comp(false, 10000);

void rev_dfs(int v, int c) {
    if (color[v] > 0) return;

    color[v] = -1;

    for (int to : rev_g[v]) {       // color: 0 - white, -1 - grey, >0 - number of component
        if (color[to] > 0 && color[to] != c) {
            outer = (visited_comp[color[to]]) ? outer : outer+1;
            visited_comp[color[to]] = true;
        }
        if (color[to] != 0) continue;
        rev_dfs(to, c);
    }

    color[v] = c;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, ans = 0;
    std::cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int from, to;
        std::cin >> from >> to;

        g[from-1].push_back(to-1); // maybe if
        rev_g[to-1].push_back(from-1);
    }

    for (int v = 0; v < n; v++) {
        dfs(v);
    }

    std::reverse(order.begin(), order.end());
    color.assign(n, 0);

    int c = 1;
    for (int v : order) {
        rev_dfs(v, c);
        ans += outer;

        visited_comp.assign(n, false); 
        outer = 0;
        
        ++c;
    }

    std::cout << ans << '\n';
}