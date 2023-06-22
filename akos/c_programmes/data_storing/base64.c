#include <stdio.h>

union base {
    char str[3];

};

int main() {
    freopen("data", "r", stdin);
    freopen("base64", "w", stdout);

    char* base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    char c1, c2, c3;
    while (scanf("%c", &c1) == 1) {
        scanf("%c%c", &c2, &c3);
        printf("%c%c%c%c", base64[c1 >> 2], base64[(c2 >> 4) | ((c1 & 3) << 4)], base64[((c2 & 15) << 2) | (c3 >> 6)], base64[c3 & 63]);
    }
}