#include <stdio.h>

int main() {
    char c;
    int x1[1000] = {0}, x2[1000] = {0};

    int sz1 = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        x1[sz1] = c - '0';
        ++sz1;
    }
    int i;
    for (i = 0; i < sz1/2; ++i) {
        int tmp = x1[i];
        x1[i] = x1[sz1-i-1];
        x1[sz1-i-1] = tmp;
    }

    int sz2 = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        x2[sz2] = c - '0';
        ++sz2;
    }
    for (i = 0; i < sz2/2; ++i) {
        int tmp = x2[i];
        x2[i] = x2[sz2-i-1];
        x2[sz2-i-1] = tmp;
    }

    int ans[1001] = {0};
    for (i = 0; i < 1000; ++i) {
        ans[i] += x1[i] + x2[i];
        if (ans[i] > 1) {
            ++ans[i+1];
            ans[i] -= 2;
        }
    }

    int _isfirst = 0;
    for (i = 1000; i >= 0; --i) {
        if (ans[i] == 1) {
            _isfirst = 1;
        }
        if (_isfirst) {
            printf("%d", ans[i]);
        }
    }

    if (!_isfirst) {
        printf("0");
    }
    printf("\n");

    return 0;
}