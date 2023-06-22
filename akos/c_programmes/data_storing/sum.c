#include <stdio.h>
#include <stdlib.h>

int main() {    
    long double* exp = (long double*)calloc(300, sizeof(long double));

    long double d;
    while (scanf("%Lf", &d) == 1) {
        long double eps = 1e-20;
        for (int i = 0; i < 300; ++i) {
            if (d < eps) {
                exp[i] += d;
                break;
            }
            eps *= 10;
        }
    }

    long double ans = 0;
    for (int i = 0; i < 300; ++i) {
        ans += exp[i];
    }

    printf("%.20Lf\n", ans);

    free(exp);
}