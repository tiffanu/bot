#include <iostream>
#include <string>

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
  size_t size = 0;

  std::string command;
  while (std::cin >> command) {

    if (command == "push"){

      int n;
      scanf("%d", &n);
      stack.push(n);
      size++;
      printf("ok\n");

    } else if (command == "pop"){

      if (stack._isempty()){
        printf("error\n");
      } else {
        printf("%d\n", stack.pop());
        size--;
      }

    } else if (command == "back") {

      if (stack._isempty()){
        printf("error\n");
      } else {
        printf("%d\n", stack.top());
      }

    } else if (command == "size") {

      printf("%zu\n", size);

    } else if (command == "clear") {

      while (!stack._isempty()){
        stack.pop();
        size--;
      }
      printf("ok\n");

    } else if (command == "exit") {

      printf("bye\n");
      break;
    }
  }

  return 0;
}