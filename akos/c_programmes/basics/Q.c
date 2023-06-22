#include <stdio.h>

int main() {
    int x;
    scanf("%d", &x);

    int a = 0, b = 0, c = 0;

    for (int _c = x - 1; _c >= 0; --_c) {
        int carry_c = (_c * _c) / x;
        if ((_c * _c) % x == _c) {
            for (int _b = x - 1; _b >= 0; --_b) {
                int carry_b = (2 * _b * _c + carry_c) / x;
                if ((2 * _b * _c + carry_c) % x == _b) {
                    for (int _a = x - 1; _a >= 0; --_a) {
                        if ( (_b *_b + 2 * _a * _c + carry_b) % x == _a) {
                            if (_a > a) {
                                a = _a;
                                b = _b;
                                c = _c;
                            } else if (_a == a && _b > b) {
                                b = _b;
                                c = _c;
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", a*x*x + b*x + c);
}