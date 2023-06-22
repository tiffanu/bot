#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    float x;
    int y, z = 0;
    scanf("%f %x", &x, &y);

    int i = 0;
    while (argv[1][i] != '\0') {
        char c = argv[1][i];
        z *= 27;
        z += (('0' <= c && c <= '9') ? c - '0' : c - 'A' + 10);
        ++i;
    }

    printf("%f", x + y + z);
}