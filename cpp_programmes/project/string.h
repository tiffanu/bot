#include <iostream>
#include <cstring>

class String {

private:
  
  void isFull() {
    if (size >= capacity) {
      delete [] str;
      while (size >= capacity) {
        capacity *= 2;
      }
      
      str = new char[capacity];
    }
  }

  char* str = nullptr;
  size_t size, capacity; 
  
public:

  friend std::ostream& operator<<(std::ostream&, const String&);
  friend std::istream& operator>>(std::istream&, const String&);

  String() { 
    size = 0;
    capacity = 10;
    str = new char[10];
  }

  String(const char* s) : String() {
    size = strlen(s);
    isFull();
    memcpy(str, s, size);
  }

  String(size_t n, char c) : String() {
    size = n;
    isFull();
    memset(str, c, size);
  }

  String(const String& s) : String() {
    size = s.size;
    isFull();
    memcpy(str, s.str, size);
  }

  String& operator=(const String& s) {
    size = s.size;
    isFull();
    memcpy(str, s.str, size);
    return *this;
  }

  ~String() {
    delete [] str;
  }

  size_t length() const {
    return size;
  }

  void push_back(char c) {
    size++;
    if (size >= capacity) {
      capacity *= 2;
      char* new_str = new char[capacity];
      memcpy(new_str, str, size - 1);
      delete [] str;
      str = new_str;
    }
    str[size-1] = c;
  }

  void pop_back() {
    if (size) {
      size--;
      if (4*size < capacity) {
        capacity /= 2;
        char* new_str = new char[++capacity];
        memcpy(new_str, str, size);
        delete [] str;
        str = new_str;
      }
    }
  }

  char& front() {
    return str[0];
  }

  const char& front() const {
    return str[0];
  }

  char& back() {
    return str[size-1];
  }

  const char& back() const {
    return str[size-1];
  }

  size_t find(const String& subs) const {
    size_t sub_size = subs.size;
    for (size_t res = 0; res <= size - sub_size; res++) {
      if (substr(res, sub_size) == subs) return res;
    }
    return length();
  }

  size_t rfind(const String& subs) const {
    size_t res = size, sub_size = subs.size;
    for (size_t i = 0; i <= size - sub_size; i++) {
      if (substr(i, sub_size) == subs) res = i;
    }
    return res;    
  }

  String substr(size_t start, size_t count) const {
    String res;
    for (size_t i = start; i < start + count ; i++) {
      res.push_back(str[i]);
    }
    return res;
  }

  bool empty() const {
    return (size == 0);
  }

  void clear() {
    delete [] str;
    str = new char[capacity];    
    size = 0;
  }

  bool operator==(const String& s) {
    if (size == s.size) {
      for (size_t i = 0; i < size; i++) {
        if (str[i] != s.str[i]) return false;
      }
      return true;
    }
    return false;
  }

  char& operator[](size_t i) {
    return str[i];
  }

  const char& operator[](size_t i) const {
    return str[i];
  }

  String& operator+=(char c) {
    push_back(c);
    return *this;
  }

  String& operator+=(const String& s) {
    for (size_t i = 0; i < s.size; i++) {
      push_back(s[i]);
    }
    return *this;
  }

  String operator+(char c) {
    String copy = *this;
    return (copy += c);
  }

  String operator+(const String& s) {
    String copy = *this;
    return (copy += s);
  }

};

String operator+(char c, const String& s) {
  return String(1, c) + s;
}

std::istream& operator>>(std::istream& in, String& s) {
  s.clear();
  char buffer[500];
  in.getline(buffer, sizeof(buffer));
  for (size_t i = 0; buffer[i]; i++) {
    s.push_back(buffer[i]);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const String& s) {
  for (size_t i = 0; i < s.length(); i++) {
    out << s.str[i];
  }
  return out;
}