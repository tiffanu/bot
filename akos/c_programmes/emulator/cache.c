#include <stdio.h>
#include <stdlib.h>

int gcd(int x, int y) {
    if (y == 0) {
        return x;
    }
    return gcd(y, x%y);
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);

    int** A = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        A[i] = (int*)malloc(n * sizeof(int));
    }

    int** B = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        B[i] = (int*)malloc(n * sizeof(int));
    }

    int** C = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i) {
        C[i] = (int*)calloc(n, sizeof(int));
    }


    int ans = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = gcd(i+1, j+1);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            B[j][i] = gcd(n-i+1, n-j+1);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[j][k];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (C[i][j] % d == 0) {
                ++ans;
            }
        }
    }

    printf("%d\n", ans);
    

    for (int i = 0; i < n; ++i) {
        free(C[i]);
    }
    free(C);

    for (int i = 0; i < n; ++i) {
        free(B[i]);
    }
    free(B);

    for (int i = 0; i < n; ++i) {
        free(A[i]);
    }
    free(A);
}