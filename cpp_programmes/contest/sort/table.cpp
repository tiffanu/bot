#include <iostream>
#include <string>
#include <algorithm>

std::string table[200];

bool cmp_table(const size_t& lhs, const size_t& rhs) {
  return (lhs < rhs) ? (table[rhs][lhs] == '-') : (table[lhs][rhs] == '+');
}

int main() {
  size_t n;
  scanf("%zu", &n);

  size_t* part = new size_t[n];

  for (size_t i = 0; i < n; i++) {
    part[i] = i;
    std::cin >> table[i];
  }

  std::sort(part, part + n, cmp_table);

  for (size_t i = 0; i < n; i++) {
    std::cout << part[i] + 1 << ' ';
  }

  delete [] part;
}