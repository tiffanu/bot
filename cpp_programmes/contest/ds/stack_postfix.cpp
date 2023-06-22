#include <stdio.h>

struct Node;

class my_stack {
public:
  using T = int;

  my_stack() {
    head = new Node(0);
  }

  ~my_stack() {
    while(!_isempty()){
      pop();
    }
    delete head;
    head = nullptr;
  }

  T pop() {
    Node* tmp = head->prev;
    head->prev = tmp->prev;
    T val = tmp->val;
    delete tmp;
    return val;
  }

  void push(T new_val) {
    Node* tmp = new Node(new_val);
    tmp->prev = head->prev;
    head->prev = tmp;
  }

  bool _isempty() const {
    return head->prev == nullptr;
  }

  T top() const {
    return head->prev->val;
  }

private:

  struct Node {
    T val;
    Node* prev;

    Node(T new_val) {
      val = new_val;
      prev = nullptr;
    }
  };

  Node* head;

};

int main() {
  my_stack stack;

  char c;
  while (scanf("%c", &c)) {
    if (c >= '0' && c <= '9') {
      stack.push(c - '0');
    } else if (c == '+') {
      int a = stack.pop(), b = stack.pop();
      stack.push(a + b);
    } else if (c == '-') {
      int a = stack.pop(), b = stack.pop();
      stack.push(b - a);
    } else if (c == '*') {
      int a = stack.pop(), b = stack.pop();
      stack.push(a * b);
    } else if (c == '=') {
      printf("%d", stack.top());
      break;
    } 
  }
  
  return 0;
}