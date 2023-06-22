#include <iostream>
#include <algorithm>
#include <string>

struct Flat {
  int num;
  char value;
  std::string amount;
};

bool cmp_flat(const Flat& lhs, const Flat& rhs) {
  if (lhs.value == rhs.value) {
    if (lhs.amount.size() == rhs.amount.size()) {
      return (lhs.amount >= rhs.amount);
    }
    return (lhs.amount.size() > rhs.amount.size());
  }
  return (lhs.value < rhs.value);
}

int main() {
  int i = 0;
  Flat flats[10001];
  while (std::cin >> flats[i].num) {
    char fict[1000];
    scanf("%[^0-9A-Za-z]", fict);

    std::string buffer;
    std::cin >> buffer;
    flats[i].value = buffer[0];

    int j = 1;
    while (buffer[j] == '0' && (j + 1 < buffer.size()) ) j++;
    flats[i++].amount = buffer.substr(j);
  }

  std::sort(flats, flats + i, cmp_flat);

  for (int j = 0; j < i; j++) {
    std::cout << flats[j].num << ' ';
  }

}