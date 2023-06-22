#include <stdio.h>

int main() {
    char c;
    long long int x;

    while ((c = getchar()) != '\n' && c != EOF) {
        x += c - '0';
        x *= 3;
    }

    printf("%lld\n", x/3);
}