#include <iostream>
#include <string>
#include <stack>

int main() {
    std::stack<char> brackets;
    std::string input;

    std::cin >> input;
    for (char c : input) {
        if (!brackets.empty()) {
            if ( ( (c == ')') && (brackets.top() == '(') ) ||
                 ( (c == ']') && (brackets.top() == '[') ) ||
                 ( (c == '}') && (brackets.top() == '{') ) ||
                 ( (c == '>') && (brackets.top() == '<') ) ) {

                brackets.pop();

            } else {
                brackets.push(c);
            }
        } else {
            brackets.push(c);
        }
    }

    brackets.empty() ? printf("YES") : printf("NO");

}