#include <iostream>
#include <vector>

using std::vector;

int inf = 32000;

int main() {
    int m, n, d;
    std::cin >> m >> n >> d;

    vector < vector < vector < int > > > a(d, vector < vector < int > > (m, vector < int > (n)));
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                std::cin >> a[i][j][k];
            }
        }
    }

    vector < vector < vector < int > > > sum(d+1, vector < vector < int > > (m+1, vector < int > (n+1, 0))); // vector of sum of elements between (i, j, k) and (0, 0, 0)
    sum[1][1][1] = a[0][0][0];

    for (int i = 2; i <= d; i++) {
        sum[i][1][1] = a[i-1][0][0] + sum[i-1][1][1];
    }

    for (int j = 2; j <= m; j++) {
        sum[1][j][1] = a[0][j-1][0] + sum[1][j-1][1];
    }   

    for (int k = 1; k <= n; k++) {
        sum[1][1][k] = a[0][0][k-1] + sum[1][1][k-1];
    }

    for (int i = 2; i <= d; i++) {
        for (int j = 2; j <= m; j++) {
            sum[i][j][1] = a[i-1][j-1][0] + sum[i-1][j][1] + sum[i][j-1][1] - sum[i-1][j-1][1];
        }
    }

    for (int j = 2; j <= m; j++) {
        for (int k = 2; k <= n; k++) {
            sum[1][j][k] = a[0][j-1][k-1] + sum[1][j-1][k] + sum[1][j][k-1] - sum[1][j-1][k-1];
        }
    }

    for (int i = 2; i <= d; i++) {
        for (int k = 2; k <= n; k++) {
            sum[i][1][k] = a[i-1][0][k-1] + sum[i-1][1][k] + sum[i][1][k-1] - sum[i-1][1][k-1];
        }
    }

    for (int i = 2; i <= d; i++) {
        for (int j = 2; j <= m; j++) {
            for (int k = 2; k <= n; k++) {
                sum[i][j][k] = a[i-1][j-1][k-1] + sum[i-1][j][k] + sum[i][j-1][k] + sum[i][j][k-1] - sum[i-1][j-1][k] - sum[i-1][j][k-1] - sum[i][j-1][k-1] + sum[i-1][j-1][k-1]; 
            }
        }
    }

    int ans = -inf;
    for (int i = 1; i <= d; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= n; k++) {
                for (int _i = 1; _i <= i; _i++) {
                    for (int _j = 1; _j <= j; _j++) {
                        for (int _k = 1; _k <= k; _k++) {
                            int curr = sum[i][j][k] - sum[_i-1][j][k] - sum[i][_j-1][k] - sum[i][j][_k-1] + sum[_i-1][_j-1][k] + sum[_i-1][j][_k-1] + sum[i][_j-1][_k-1] - sum[_i-1][_j-1][_k-1];
                            ans = (curr > ans) ? curr : ans;
                            //std::cout << curr << '\n';
                        }
                    }
                }
            }
        }
    }


    std::cout << ans << '\n';
/*
    std::cout << '\n';
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                std::cout << sum[i][j][k] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

*/
}