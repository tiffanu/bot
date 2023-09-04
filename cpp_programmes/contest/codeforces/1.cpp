#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

using std::vector;
using std::string;
using std::cin, std::cout;

int log_2(int n) {
    int ans = 0;
    while (n) {
        n >>= 1;
        ++ans;
    }
    return ans-1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    const long long inf = 2e9;


    while (t--) {
        int n;
        cin >> n;

        vector<int> log;
        log.push_back(n);

        while (n > 1) {
            int d_prep = n - (1 << log_2(n));
            if (d_prep != 0 && n % d_prep == 0) {
                n -= d_prep;
                log.push_back(n);
                continue;
            }
            if (n % 2 == 1) {
                --n;
                log.push_back(n);
            } else {
                n /= 2;
                log.push_back(n);
            }
        }

        cout << log.size() << '\n';
        for (int el : log) {
            cout << el << ' ';
        }
        cout << '\n';
    }
}