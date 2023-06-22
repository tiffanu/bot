#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long long int x;
    scanf("%lld", &x);
    printf("%llo\n", x);

    return 0;
}