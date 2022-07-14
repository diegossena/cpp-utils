#pragma once
#include <cstdint>
#include <cstring>
using namespace std;
#include "Object.hpp"
#include "Iterator.hpp"
uint64_t String_instances = 0;
class String : public Object {
  char* __string;
  uint64_t __length = 0;
public:
  // refs
  const uint64_t& length = __length;
  // constructors
  template<typename T, typename... Args>
  String(T str, Args... args) : String(
    String(str) + String(args...)
  ) { }
  template<typename... Args>
  String(int str, Args... args) : __string(
    to__string(str) + String(args...).__string
  ) { }
  //
  String() : __string((char*)malloc(1)) {
    __string[0] = '\0';
    String_instances++;
  }
  String(char str) : __length(1) {
    __string = (char*)malloc(2);
    String_instances++;
    __string[0] = str;
    __string[1] = '\0';
  }
  String(char* str, uint64_t length) : __string(str), __length(length) {}
  String(const char* str) : __length(strlen(str)) {
    uint64_t size = __length + 1;
    __string = (char*)memcpy(malloc(size), str, size);
    String_instances++;
  }
  ~String() {
    free(__string);
    String_instances--;
  }
  // methods
  String toLowerCase() {
    String lower_case_str = __string;
    for (uint64_t i = 0; i < lower_case_str.length; i++)
    {
      if (lower_case_str.__string[i] >= 65 && lower_case_str.__string[i] <= 90)
      {
        lower_case_str.__string[i] += 32;
      }
    }
    return lower_case_str;
  }
  String toUpperCase() {
    String lower_case_str = __string;
    for (uint64_t i = 0; i < lower_case_str.length; i++)
      if (lower_case_str.__string[i] >= 97 && lower_case_str.__string[i] <= 122)
        lower_case_str.__string[i] -= 32;
    return lower_case_str;
  }
  const char* toString() {
    return __string;
  }
  // static methods
  static void printChart(uint8_t width = 10) {
    for (uint16_t c = 0; c <= 255; c++) {
      for (uint16_t x = 0; x < width && c <= 255; x++, c++) {
        cout << "[" << c << " ";
        if (c < 10)
          cout << "  ";
        else if (c < 100)
          cout << " ";
        cout << (char)c << "]";
      }
      cout << endl;
    }
  }
  // conversions
  operator const char* () { return __string; }
  // operators
  void operator+=(
    const String src
    ) {
    uint64_t length = __length + src.__length;
    char* str = (char*)malloc(length + 1);
    String_instances++;
    memcpy(str, __string, __length);
    memcpy(str + __length, src.__string, src.__length + 1);
    free(__string);
    String_instances--;
    __string = str;
    __length = length;
  }
  char& operator[] (uint64_t i) { return __string[i]; }
  friend ostream&
    operator<<(
      ostream& os,
      const String& str) {
    os << str.__string;
    return os;
  }
  String operator+(
    const String& src
    ) {
    uint64_t length = __length + src.__length;
    char* str = (char*)malloc(length + 1);
    String_instances++;
    memcpy(str, __string, __length);
    memcpy(str + __length, src.__string, src.__length + 1);
    return String(str, length);
  }
  void operator=(
    const String& str
    ) {
    free(__string);
    uint64_t length = str.__length + 1;
    __string = (char*)memcpy(malloc(length), str.__string, length);
    String_instances++;
    __length = str.__length;
  }
  using StringIterator = Iterator<char>;
  StringIterator begin() { return StringIterator(__string); }
  StringIterator end() { return StringIterator(__string + __length); }
};