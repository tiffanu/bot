#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _LongN {
	char* dig;	// массив для хранения числа:
                // a[0] * 100^0 + a[1] * 100^1 + .. + a[n - 1] * 100^(n-1)
	int n; 			// размер числа в разрядах
	char sign;	// знак числа
};
typedef struct _LongN LongN;

void print(LongN l) {
    printf("%d\n", l.n);
    if (l.sign) printf("-");
    for (int i = l.n; i > 0; --i) {
        if (l.dig[i-1] < 10 && i != l.n) {
            printf("0%d", l.dig[i-1]);
        } else {
            printf("%d", l.dig[i-1]);
        }
    }

}

LongN getLongN(char* s) { // malloc
    LongN res;
    res.dig = (char*)malloc(100 * sizeof(char));

    int start = (s[0] == '-' || s[0] == '+') ? 1 : 0;

    res.sign = 0;
    if (s[0] == '-') {
        res.sign = 1;
    }

    res.n = (strlen(s) + 1 - start) / 2;

    int i = 0, pos;
    for (pos = strlen(s) - 1; pos > start; pos -= 2) {
        res.dig[i] = 10 * (s[pos-1] - '0') + (s[pos] - '0');
        ++i;
    }

    if (pos == 1 && start) {
        res.dig[i] = s[1] - '0';
    } else if (pos == 0 && !start) {
        res.dig[i] = s[0] - '0';
    }
    
    return res;
}