#include <stdio.h>

char buffer[1000000];

char input[1000000];
unsigned int idx = 0, len = 0;

static int fast_readchar() {
    if (idx == len) {
        len = fread(input, 1, 1000000, stdin);
        idx = 0;
    }
    return (len ? input[idx++] : -1);
}

int w_idx = 0;
void fast_writechar(char c) {
    if (w_idx == 1000000) {
        fwrite(buffer, 1, 1000000, stdout);
        w_idx = 0;
    }
    buffer[w_idx++] = c;
}

void fast_flush() {
    if (w_idx) {
        fwrite(buffer, 1, w_idx, stdout);
        w_idx = 0;
    }
}

int main() {
    char c;
    int is_first = 0;
    while ((c = fast_readchar()) >= '0') {
        int num;
        if ('0' <= c && c <= '9') {
            num = c - '0';
        } else {
            num = c - 'A' + 10;
        }

        for (int mask = 8; mask != 0; mask >>= 1) {
            if (mask & num) {
                is_first = 1;
                fast_writechar('1');
            } else if (is_first) {
                fast_writechar('0');
            }
        }
    }

    if (!is_first) {
        fast_writechar('0');
    }
    fast_flush();
}