#include <stdio.h>

int main() {
    int m[4];
    scanf("%d.%d.%d.%d", &m[0], &m[1], &m[2], &m[3]);

    int s[4];
    scanf("%d.%d.%d.%d", &s[0], &s[1], &s[2], &s[3]);

    for (int i = 0; i < 4; ++i) {
        int ans = 0;
        for (int mask = (1 << 7); mask != 0; mask >>= 1) {
            if (s[i] & mask) {
                ans = (m[i] & mask) ? ans+1 : ans;
                ans *= 2;
            } else {
                ++ans;
                ans *= 2;
            }
        }
        printf("%d", ans/2);
        if (i < 3) {
            putchar('.');
        }
    }        
    putchar('\n');
}