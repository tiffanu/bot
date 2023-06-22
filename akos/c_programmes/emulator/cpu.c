#include <stdio.h>
#include <stdlib.h>

// #define REGISTERS 4

int main() {
    int num = 4;

    #ifdef REGISTERS
    num = REGISTERS;
    #endif

    unsigned* reg = (unsigned*)calloc(num, sizeof(unsigned));

    int command;
    scanf("%d", &command);

    while (command) {
        if (command == 1) {
            int first, second;
            scanf("%d %d\n", &first, &second);

            if (num + 4 < first || num + 4 < second) {
                printf("-1\n");
                return 0;
            }

            reg[first-5] += reg[second-5];
            reg[first-5] %= 256;

        } else if (command == 2) {        
            int first, second;
            scanf("%d %d\n", &first, &second);

            if (num + 4 < first || num + 4 < second) {
                printf("-1\n");
                return 0;
            }

            reg[first-5] -= reg[second-5];
            reg[first-5] %= 256;
        
        } else if (command == 3) {
            unsigned first, x;
            scanf("%d %d\n", &first, &x);

            if (num + 4 < first) {
                printf("-1\n");
                return 0;
            }

            reg[first-5] = x;
            reg[first-5] %= 256;
        
        } else if (command == 4) {
            for (int i = 0; i < num; ++i) {
                printf("%d ", reg[i]);
            }
        }

        scanf("%d", &command);
    }

    free(reg);

    return 0;
}