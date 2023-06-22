#include <stdio.h>

int main() {
    freopen("bit_3.dat", "r", stdin);
    freopen("bit_3.ans", "w", stdout);

    char c = getchar();
    if ('0' <= c && c <= '9') {
        c -= '0';
    } else {
        c -= 'a' - 10;
    }

    c &= 3;
    switch (c) {
    case 0:
        printf("bn\n");
        break;
    
    case 1:
        printf("rd\n");
        break;
    
    case 2:
        printf("bw\n");
        break;
    
    case 3:
        printf("bk\n");
        break;
    
    default:
        break;
    }
}