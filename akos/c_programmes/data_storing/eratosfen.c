#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    char* er = (char*)calloc(200000008/8, sizeof(char));
    int ans = 0;

    int x;
    scanf("%d", &x);

    for (int i = 2; i*i <= x; ++i) {
        if ( !((er[i/8] >> (i%8)) & 1) ) {         
            for (int j = 2 * i; j <= x; j += i) {
                er[j/8] |= (1 << (j%8));
            }
        }
    }

    for (int i = 2; i <= x; ++i) {
        if ( !((er[i/8] >> (i%8)) & 1) ) {
            ++ans;
        }
    }

    free(er);

    printf("%d\n", ans);
}