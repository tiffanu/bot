#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); std::cout.tie(NULL);

    int n;
    std::cin >> n;

    int** d = new int*[n];

    for (int i = 0; i < n; ++i) {
        d[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> d[i][j];
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int new_d = d[i][k] + d[k][j];
                d[i][j] = (d[i][j] < new_d) ? d[i][j] : new_d;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << d[i][j] << ' ';
        }
        std::cout << '\n';
    }

    for (int i = 0; i < n; ++i) {
        delete [] d[i];
    }

    delete [] d;
}