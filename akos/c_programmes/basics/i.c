/*
The rules in the Roman numeral system are the following. Mentioned letters I, V, X, L, C, D and M (Roman digits) 
correspond to numbers 1, 5, 10, 50, 100, 500 and 1000 respectively. A number in the Roman numeral system cannot 
have more than three identical letters in a row. Each of the characters V, L, D can appear at most once. 
Letters I, X, C can be put before letters X, C and M to make up 9, 90 and 900, or before letters V, L 
and D to make up 4, 40 and 400 respectively. IX and IV cannot be followed by anything else, XL and XC 
can be followed only by V or I, CD and CM only by L, X, V or I. For example, IVII is not a correct 
Roman numeral. In other cases, one digit put after another means just the sum of the digits. IV, XC, . . . 
Lastly, a smaller digit must be put after a bigger or identical one (here combinations are considered like 
digits). So representation of a number in the Roman numeral system is unique. 
*/

#include <stdio.h>

int isRoman(char c) {
    return (c == 'I' || c == 'i' || c == 'V' || c == 'v' || c == 'X' || c == 'x' || 
            c == 'L' || c == 'l' || c == 'C' || c == 'c' || c == 'D' || c == 'd' || c == 'M' || c == 'm');
}

int main() {
    int ammount[130] = {0};

    char c;
    while ((c = getchar()) != '\n' && isRoman(c)) {  // maybe isRoman(c) will be counted first (?)
        if ('a' <= c && c <= 'z') {
            ++ammount[c - 'a' + 'A'];
        } else {
            ++ammount[c];
        }
    }

    int num_m = ammount['M'];
    num_m = (num_m >= 4) ? 4 : num_m;
    while (num_m > 1) {
        putchar('M');
        --num_m;
    }

    int num_d = ammount['D'], num_c = ammount['C'];
    if (num_c >= 2 && num_d) {
        putchar('D'); 
        --num_d;
        for (int i = 0; i < 3 && i < num_c; ++i) {     // MMMDCCC
            putchar('C');
            --num_c;
        }
    } else if (num_c && num_m) {
        putchar('C'); putchar('M');                    // MMMCM
        --num_c; --num_m;
    } else if (num_c && num_d && !num_m) {
        putchar('D'); putchar('C');                    // MMMDC
        --num_d; --num_c;
    }




    //     putchar('C'); putchar('M');
    // } else if (num_c && num_d) {
    //     putchar('D'); putchar('C');
    // } else if (num_d) {
    //     putchar('D');
    // } else if (num_c) {

    // }

}