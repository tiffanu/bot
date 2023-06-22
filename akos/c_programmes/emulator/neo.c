#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct anomaly {
    char name_of_anomaly[256];
    int number_of_anomaly;
};

char* whatisyourname() {
    char* name = (char*)malloc(sizeof(char) * 257);

    for (int i = 0; i <= 256; ++i) {
        name[i] = 'a';
    }

    *(name+256) = 0;

    return name;
}

int main() {
    struct anomaly neo;
    neo.number_of_anomaly = 6;
    strcpy(neo.name_of_anomaly, whatisyourname());

    for (int i = 0; i <= 256; ++i) { 
        printf("%d %x\n", i, neo.name_of_anomaly[i]);
    }
}