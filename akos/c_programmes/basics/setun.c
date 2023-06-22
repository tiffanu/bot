#include <stdio.h>

int main() {
    int x[1000] = {0}, y[1000] = {0};

    char c;

    int sz1 = 0;
    while ((c = getchar()) != '\n') {
        x[sz1++] = (c == '$') ? -1 : c - '0';
    }

    int sz2 = 0;
    while ((c = getchar()) != '\n') {
        y[sz2++] = (c == '$') ? -1 : c - '0';
    }

    for (int i = 0; i < sz1/2; ++i) {
        int tmp = x[i];
        x[i] = x[sz1-i-1];
        x[sz1-i-1] = tmp;
    }
    for (int i = 0; i < sz2/2; ++i) {
        int tmp = y[i];
        y[i] = y[sz2-i-1];
        y[sz2-i-1] = tmp;
    }

    int ans[1001] = {0};
    for (int i = 0; i < 1000; ++i) {
        ans[i] += x[i] + y[i];
        if (ans[i] < -1) {
            --ans[i+1];
            ans[i] += 3;
        } else if (ans[i] > 1) {
            ++ans[i+1];
            ans[i] -= 3;
        }
    }

    int i;
    int _isfirst = 0;
    for (i = 1000; i >= 0; --i) {
        if (ans[i]) {
            _isfirst = 1;
            break;
        }
    }
    for (i; i >= 0; --i) {
        putchar((ans[i] == -1) ? '$' : ans[i] + '0');
    }

    if (!_isfirst) {
        putchar('0');
    }
    putchar('\n');

    return 0;
}