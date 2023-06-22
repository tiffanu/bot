#include <stdio.h>

int main() {
    int ans = 0;
    int r2a[255] = {0};
    r2a['I'] = 1;
    r2a['V'] = 5;    
    r2a['X'] = 10;
    r2a['L'] = 50;
    r2a['C'] = 100;
    r2a['D'] = 500;
    r2a['M'] = 1000;


    char c1 = getchar(), c2;
    ans += r2a[c1];

    while ((c2 = getchar()) != '\n') {
        if (r2a[c2] > r2a[c1]) {
            ans -= r2a[c1];
            ans += r2a[c2] - r2a[c1];
            c1 = c2;
            continue;
        }
        ans += r2a[c2];
        c1 = c2;
    }

    printf("%d\n", ans);
}