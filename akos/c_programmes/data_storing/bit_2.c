#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]) {
    int i = 0;
    for (i; envp[i] != NULL; ++i) {
        if (!strncmp(envp[i], "CODE=", 5)) {
            break;
        }
    }

    char c = envp[i][strlen(envp[i]) - 1];
    if ('0' <= c && c <= '9') {
        c -= '0';
    } else {
        c -= 'a' - 10;
    }

    if (c & 4) {
        printf("ha\n");
    } else {
        printf("nh\n");
    }
}