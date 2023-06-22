#include <stdio.h>
#include <stdint.h>

union data {
    uint64_t u64;
    uint8_t arr[8];
    uint32_t a32[2];
};

union data convert(union data x) {
    for (int i = 0; i < 4; ++i) {
        uint8_t tmp = x.arr[i];
        x.arr[i] = x.arr[7-i];
        x.arr[7-i] = tmp;
    }

    return x;
}

int main() {
    union data x;
    x.u64 = 0x9ABCDEF0;
    union data y = convert(x);
    printf("%lx\n", y.u64);
}