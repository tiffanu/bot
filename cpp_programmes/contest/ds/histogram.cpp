#include <stdio.h>
#include <stack>

struct Column {
  long long h;
  int left;
  int right;
};

int main() {
  size_t n;
  scanf("%zu", &n);

  long long ans = 0;
  std::stack<Column> s;

  for (size_t i = 0; i < n; i++) {
    Column col;
    col.left = i;
    scanf("%lld", &col.h);

    while (!s.empty() && s.top().h > col.h) {
      long long area = s.top().h * (i - s.top().left);
      ans = (ans > area) ? ans : area;
      col.left = s.top().left;
      s.pop();
    }

    if (s.empty()) col.left = 0;

    s.push(col);
  }

  while (!s.empty()) {
    long long area = s.top().h * (n - s.top().left);
    ans = (ans > area) ? ans : area;
    s.pop();
  }
  
  printf("%lld", ans);

}