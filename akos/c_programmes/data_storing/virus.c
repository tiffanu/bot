#include <stdio.h>
#include <stdlib.h>

int main() {
    int ans = 0;

    int virused;
    scanf("%d", &virused);

    int num;
    scanf("%d", &num);

    char* er = (char*)calloc(1 + num/8, sizeof(char));           // need num/16
    int v[100];

    for (int i = 0; i < virused; ++i) {
        scanf("%d", &v[i]);
        er[v[i]/8] |= (1 << (v[i] % 8));
    }

    int carry, i;
    for (int k = 0; k < virused; ++k) {
        carry = 0;
        i = v[k];
        if ( (er[i/8] >> (i%8)) & 1 ) {         
            for (int j = 2*i + carry; j < num; j += i + (++carry)) {
                er[j/8] |= (1 << (j%8));
            }
        }
    }

    for (int i = 0; i < num; ++i) {
        if ( (er[i/8] >> (i%8)) & 1 ) {
            ++ans;
        }
    }

    free(er);

    printf("%d\n", ans);
}
