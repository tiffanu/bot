#include <iostream>

using std::cin;
using std::cout;

int path(int i, int j, int** triangle, int** cache, int n) {
    if (i + j == n - 1) return cache[i][j] = triangle[i][j];
    
    return cache[i][j] = (cache[i][j]) ? cache[i][j] : triangle[i][j] + std::max(path(i, j+1, triangle, cache, n), path(i+1, j, triangle, cache, n));
}

int main() {
    int n;
    cin >> n;

    int **triangle = new int*[n];

    for (int i = 0; i < n; i++) {
        triangle[i] = new int[n];
    }

    for (int k = 0; k < n; k++) {
        int i = k, j = 0;
        while (j <= k) {
            cin >> triangle[i--][j++];
        }
    }

    int **cache = new int*[n];

    for (int i = 0; i < n; i++) {
        cache[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cache[i][j] = 0;
        }
    }

    cout << path(0, 0, triangle, cache, n) << '\n';

    for (int i = 0; i < n; i++) {
        delete [] cache[i];
    }

    delete [] cache;

    for (int i = 0; i < n; i++) {
        delete [] triangle[i];
    }

    delete [] triangle;
}