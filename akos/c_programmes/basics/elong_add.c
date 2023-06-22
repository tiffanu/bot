#include <stdio.h>
#include <stdlib.h>

#define N 100
struct _Decimal {
    char a[N];   // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;       // наибольшая степень десяти
};
typedef struct _Decimal Decimal;

Decimal zero = {{0}, 0};    // представление 0 в виде структуры

void print(Decimal d) {
    for (int i = d.n; i >= 0; --i) {
        printf("%d", d.a[i]);
    }
    printf("\n%u", d.n);
}

Decimal add (Decimal a, Decimal b) {
    Decimal res;
    for (int i = 0; i <= N; ++i) {
        res.a[i] = 0;
    }
    res.n = (a.n > b.n) ? a.n : b.n;

    unsigned int i;
    for (i = 0; i <= a.n && i <= b.n; ++i) {
        res.a[i] += a.a[i] + b.a[i];
        if (res.a[i] >= 10) {
            ++res.a[i+1];
            res.a[i] -= 10;
        }
    }

    for (; i <= a.n || i <= b.n; ++i) {
        res.a[i] += (a.n > b.n) ? a.a[i] : b.a[i];
        if (res.a[i] >= 10) {
            ++res.a[i+1];
            res.a[i] -= 10;
        }
    }

    if (res.a[i]) {
        ++res.n;
    }

    return res;
}

int main() {
    Decimal a = {{5}, 0};  // set number 147
    Decimal b = {{6}, 0};     // set number 13
    Decimal res;
    
    res = add(a, b);             // res = a+b = 147+13 = 160

    print(res);
    printf("\n");
    
    return 0;
}