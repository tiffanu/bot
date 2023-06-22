#include <stdio.h>

int gcd(int c, int x) {
    if (x == 0) {
        return c;
    }
    return gcd(x, c%x);
}

int main() {
    float f;
    scanf("%f", &f);

    int z = (int)f;

    float c = f - z;
    c = (c > 0) ? c : -c;

    c *= 10000000;

    int d = gcd(c, 10000000);

    int a = c/d, b = 10000000/d;

    printf("%d (%d/%d)\n", z, a, b);  // if z == f
}