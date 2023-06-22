#include <stdio.h>
#include <string.h>

union u {
    char data[10000];
    long double ldb;
    double db;
    float fl;
};

int main() {
    char str[10000];
    int size;

    scanf("%s", str);
    if (!strncmp(str, "float", 5)) {
        size = sizeof(float);

        union u f;

        scanf("%f", &f.fl);

        for (int i = size - 1; i >= 0; --i) {
            for (int mask = 128; mask != 0; mask >>= 1) {
                if (f.data[i] & mask) {
                    putchar('1');
                } else {
                    putchar('0');
                }
                if (mask == 16) {
                    putchar(' ');
                }
            }
            putchar(' ');
        }

    } else if (!strncmp(str, "double", 6)) {
        size = sizeof(double);

        union u d;

        scanf("%lf", &d.db);

        for (int i = size - 1; i >= 0; --i) {
            for (int mask = 128; mask != 0; mask >>= 1) {
                if (d.data[i] & mask) {
                    putchar('1');
                } else {
                    putchar('0');
                }
                if (mask == 16) {
                    putchar(' ');
                }
            }
            putchar(' ');
        }

    } else if (!strncmp(str, "long", 4)) {
        size = sizeof(long double);

        union u ld;

        scanf("%s %Lf", str, &ld.ldb);

        for (int i = size - 1; i >= 0; --i) {
            for (int mask = 128; mask != 0; mask >>= 1) {
                if (ld.data[i] & mask) {
                    putchar('1');
                } else {
                    putchar('0');
                }
                if (mask == 16) {
                    putchar(' ');
                }
            }
            putchar(' ');
        }

    } else {
        return 0;
    }
    putchar('\n');

    return 0;
}