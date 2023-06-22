#include <stdio.h>

int main() {
    char c;
    long double z = 0;
    while ((c = getchar()) != '\n') {
        z *= 2;
        if (c == '1') {
            z += 1;
        } else if (c == '.') {
            break;
        }
    }

    z /= 2;
    if (c == '\n') {
        z *= 2;
    }
    
    if (c == '.') {
        long double deg = 1;
        while ((c = getchar()) != '\n') {
            deg /= 2;
            if (c == '1') {
                z +=  deg;
            }
        }
    }
    
    printf("%.12Lf\n", z);
}