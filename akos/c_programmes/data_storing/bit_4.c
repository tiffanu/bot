#include <stdio.h>

int main() {
    char c1 = getchar();
    if ('0' <= c1 && c1 <= '9') {
        c1 -= '0';
    } else {
        c1 -= 'a' - 10;
    }

    char c2 = getchar();
    if ('0' <= c2 && c2 <= '9') {
        c2 -= '0';
    } else {
        c2 -= 'a' - 10;
    }

    if (c2 & 1) {
        printf("ma ");
    } else {
        printf("fe ");
    }

    if (c2 & 2) {
        printf("cl ");
    } else {
        printf("du ");
    }

    if (c2 & 4) {
        printf("ha ");
    } else {
        printf("nh ");
    }

    if (c2 & 8) {
        printf("tr ");
    } else {
        printf("sk ");
    }

    switch (c1 & 3) {
    case 0:
        printf("bn ");
        break;
    case 1:
        printf("rd ");
        break;
    case 2:
        printf("bw ");
        break;
    case 3:
        printf("bk ");
        break;
    default:
        break;
    }

    switch ( (c1 >> 2) & 3) {
    case 0:
        printf("bu\n");
        break;
    case 1:
        printf("ge\n");
        break;
    case 2:
        printf("gy\n");
        break;
    case 3:
        printf("da\n");
        break;
    default:
        break;
    }
}