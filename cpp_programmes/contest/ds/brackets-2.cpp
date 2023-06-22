#include <stdio.h>
 
int main(){
    char* line = new char[102400];
 
    size_t i = 0;
    while (scanf("%c", &line[i]) == 1) {
        if (i) {
            if ( ( (line[i] == ')') && (line[i-1] == '(') ) ||
                 ( (line[i] == ']') && (line[i-1] == '[') ) ||
                 ( (line[i] == '}') && (line[i-1] == '{') ) ||
                 ( (line[i] == '>') && (line[i-1] == '<') ) ) {
 
                i--;  
                 
            } else {
                i++;
            }
                
        } else {
            i++;
        }
    }
 
    i-1 ? printf("NO") : printf("YES");
 
    delete [] line;
}