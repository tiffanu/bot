#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;
using std::set;

vector<vector<int>> g(20000);

int timer = 0;
vector<int> tin(20000);           //                             | tin[v]
vector<int> fup(20000);           // from E-maxx:   fup[v] = min | tin[p], for all (v, p) - back edges
                                  //                             | fup[to], for all (v, to) - tree edges
vector<int> parent(20000);
vector<bool> color(20000, false); // false -- unused, true -- used

set<int> ans;

void dfs(int v, int p = -1) {

    tin[v] = fup[v] = timer++;
    color[v] = true;
    parent[v] = p;

    int child = 0;
    for (int& to : g[v]) {
        if (p == to) continue;

        if (color[to] == true) {

            fup[v] = (fup[v] < tin[to]) ? fup[v] : tin[to];
        
        } else {

            dfs(to, v);
            fup[v] = (fup[v] < fup[to]) ? fup[v] : fup[to];

            if (fup[to] >= tin[v] && p != -1) ans.insert(v);

            ++child;
        }

    }

    if (p == -1 && child >= 2) ans.insert(v); 
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int from, to;
        std::cin >> from >> to;

        g[from-1].push_back(to-1);
        g[to-1].push_back(from-1);
    }

    dfs(0);

    std::cout << ans.size() << '\n';
    for (const int& el : ans) std::cout << el+1 << ' ';
}