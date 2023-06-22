#include <stdio.h>

int main() {
    int n, k;
    scanf("%d\n", &n);

    int x = 0;
    char c;
    while ((c = getchar()) != '\n') {
        x *= n;
        if ('0' <= c && c <= '9') {
            x += c - '0';
        } else {
            x += c - 'A' + 10;
        }
    }
    if (!x) {
        putchar('0');
        return 0;
    }
    
    char buff[32];
    int i = 0;

    scanf("%d", &k);
    while (x) {
        int r = x % k;
        if (r >= 10) {
            buff[i++] = 'A' + r - 10;
        } else {
            buff[i++] = '0' + r;
        }
        x /= k;
    }

    for (i; i > 0; --i) {
        putchar(buff[i-1]);
    }
}