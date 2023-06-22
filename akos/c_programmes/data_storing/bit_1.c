#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char c = argv[1][strlen(argv[1]) - 1];
    if ('0' <= c && c <= '9') {
        c -= '0';
    } else {
        c -= 'a' - 10;
    }
    if (c & 1) {
        printf("ma\n");
    } else {
        printf("fe\n");
    }
}