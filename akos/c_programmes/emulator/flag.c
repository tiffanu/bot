#include <stdio.h>
#include <stdlib.h>

unsigned char ZeroFlag = 0;

int main() {
    int num = 4;

    unsigned char reg[4] = {0};

    int command;
    while (scanf("%d", &command) == 1) {
        if ((command & 0x80) && !ZeroFlag) {
            continue;
        }

        int _command = command & 0x7f;
        if (_command == 0) {
            break;
        } else if (_command == 1) {
            int first, second;
            scanf("%d %d\n", &first, &second);

            if ( (reg[first-5] += (reg[second-5] % 256)) % 256 ) {
                ZeroFlag = 0;
            } else {
                ZeroFlag = 1;
            }
            reg[first-5] %= 256;

        } else if (_command == 2) {   
            int first, second;
            scanf("%d %d\n", &first, &second);

            if ( (reg[first-5] -= (reg[second-5] % 256)) % 256 ) {
                ZeroFlag = 0;
            } else {
                ZeroFlag = 1;
            }
            reg[first-5] %= 256;
        
        } else if (_command == 3) {
            unsigned first, x;
            scanf("%d %d\n", &first, &x);

            if ( (reg[first-5] = (x % 256)) % 256 ) {
                ZeroFlag = 0;
            } else {
                ZeroFlag = 1;
            }
            reg[first-5] %= 256;
        
        } else if (_command == 4) {
            for (int i = 0; i < num; ++i) {
                printf("%d ", reg[i] % 256);
            }
            ZeroFlag = 0;
        }
    }

    return 0;
}