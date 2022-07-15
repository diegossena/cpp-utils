#pragma once
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cmath> 
using namespace std;
#include "Object.hpp"
#include "Iterator.hpp"
#define STRING_DEBUG false
#if STRING_DEBUG
int64_t String_instances = 0;
#endif
class String : public Object {
  char* __string;
  uint64_t __length = 0;
public:
  // refs
  const uint64_t& length = __length;
  // constructors
  template<typename T, typename... Args>
  String(T str, Args... args) : String(String(str) + String(args...)) {}
  String(char str) : __length(1) {
    __string = (char*)malloc(2);
    sprintf(__string, "%c", str);
#if STRING_DEBUG
    String_instances++;
    cout
      << String_instances
      << " String(char str) "
      << "str='" << str << "'"
      << endl;
#endif
  }
  String(char* str, uint64_t length) : __string(str), __length(length) {}
  String(const char* str, uint64_t length) : __length(length) {
    uint64_t size = __length + 1;
    __string = (char*)memcpy(malloc(size), str, size);
#if STRING_DEBUG
    String_instances++;
    cout
      << String_instances
      << " String(const char* str,uint64_t length){"
      << "str='" << str << "';"
      << "length=" << length
      << "}"
      << endl;
#endif
  }
  String() : String((const char*)"", (uint64_t)0) {}
  String(const String& str) : String((const char*)str.__string, str.__length) {}
  String(const char* str) : String(str, strlen(str)) {}
  String(int num) : __length((ceil(log10(num)) + 1) * sizeof(char)) {
    uint64_t size = __length + 1;
    __string = (char*)malloc(size);
    sprintf(__string, "%d", num);
#if STRING_DEBUG
    String_instances++;
    cout << String_instances << " String(int num) " << "num=" << num << endl;
#endif
  }
  ~String() {
#if STRING_DEBUG
    String_instances--;
    cout << String_instances << " ~String='" << __string << '\'' << endl;
#endif
    free(__string);
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
    const String& src
    ) {
    uint64_t length = __length + src.__length;
    char* str = (char*)malloc(length + 1);
    memcpy(str, __string, __length);
    memcpy(str + __length, src.__string, src.__length + 1);
    free(__string);
    __string = str;
    __length = length;
#if STRING_DEBUG
    cout
      << String_instances
      << " String=+('" << __string << "' =+ '" << src << "')"
      << endl;
#endif
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
    memcpy(str, __string, __length);
    memcpy(str + __length, src.__string, src.__length + 1);
#if STRING_DEBUG
    String_instances++;
    cout
      << String_instances
      << " String('" << __string << "' + '" << src << "')"
      << endl;
#endif
    return { str, length };
  }
  String operator*(
    uint16_t multiplier
    ) {
    uint64_t length = __length * multiplier;
    uint64_t size = length + 1;
    char* new_char = (char*)malloc(size);
    while (multiplier--) {
      uint64_t i = __length;
      while (i--)
        new_char[multiplier * __length + i] = __string[i];
    }
    new_char[length] = '\0';
#if STRING_DEBUG
    String_instances++;
    cout
      << String_instances
      << " String*(uint16_t multiplier){"
      << "multiplier=" << multiplier << "}"
      << endl;
#endif
    return { new_char, length };
  }
  void operator=(
    const String& src
    ) {
    free(__string);
    uint64_t length = src.__length + 1;
    __string = (char*)memcpy(malloc(length), src.__string, length);
    __length = src.__length;
#if STRING_DEBUG
    cout
      << String_instances
      << " String('" << __string << "' = '" << src << "')"
      << endl;
#endif
  }
  using StringIterator = Iterator<char>;
  StringIterator begin() { return StringIterator(__string); }
  StringIterator end() { return StringIterator(__string + __length); }
};