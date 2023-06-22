#include <stdio.h>
#include <string.h>

int main() {
    int c = 0;
    char s[2];
    while (scanf("%2s", s) != EOF) {
        if (!strncmp(s, "ma", 2)) {
            c |= 1;
        } else if (!strncmp(s, "cl", 2)) {
            c |= 2;
        } else if (!strncmp(s, "ha", 2)) {
            c |= 4;
        } else if (!strncmp(s, "tr", 2)) {
            c |= 8;            
        } else if (!strncmp(s, "rd", 2)) {
            c |= 16;            
        } else if (!strncmp(s, "bw", 2)) {
            c |= 32;            
        } else if (!strncmp(s, "bk", 2)) {
            c |= 48;            
        } else if (!strncmp(s, "ge", 2)) {
            c |= 64;            
        } else if (!strncmp(s, "gy", 2)) {
            c |= 128;            
        } else if (!strncmp(s, "da", 2)) {
            c |= 192;            
        }
    }

    printf("%x\n", c);
}