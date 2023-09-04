#include <iostream>
#include <stack>

class Queue {
public:
    void push_back(int x) {
        add.push(x);
    }

    void push_front(int x) {
        del.push(x);
    }

    int front() {
        if (del.empty()) {
            while (!add.empty()) {
                del.push(add.top());
                add.pop();
            }
        }
        return del.top();
    }

    void pop_front() {
        if (del.empty()) {
            while (!add.empty()) {
                del.push(add.top());
                add.pop();
            }
        }
        del.pop();
    }
private:
    std::stack<int> add;
    std::stack<int> del;
};

int main() {
    size_t n;
    scanf("%zu", &n);

    Queue half1, half2;
    int size1 = 0, size2 = 0;         // inv: size1 >= size2 by not more than 1
    for (size_t i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);

        if (c == '+') {
            int num;
            scanf("%d", &num);
            
            if (size1 == size2) {
                half2.push_back(num);

                half1.push_back(half2.front());
                half2.pop_front();

                ++size1;
            } else {
                half2.push_back(num);

                ++size2;
            }
        } else if (c == '*') {
            int num;
            scanf("%d", &num);            

            if (size1 == size2) {
                half1.push_back(num);

                ++size1;
            } else {
                half2.push_front(num);

                ++size2;
            }
        } else if (c == '-') {
            if (size1 == size2) {
                printf("%d\n", half1.front());
                half1.pop_front();

                half1.push_back(half2.front());
                half2.pop_front();

                --size2;
            } else {
                printf("%d\n", half1.front());
                half1.pop_front(); 

                --size1;
            }
        }
    }
}