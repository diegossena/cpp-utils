#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class String {
  string __string = "";
  uint64_t __length = __string.length();
public:
  // refs
  const size_t& length = __length;
  // Conversion
  operator const char* () {
    return __string.c_str();
  }
  operator const bool() {
    return !__string.empty();
  }
  // with no arguments
  String() {}
  // Copy Constructor
  // String(string str) : __string(str) {}
  // String(const char* str) : __string(str) {}
  // String(char str) : __string(1, str) {}
  // String(int number) : __string(to__string(number)) {}
  template<typename T, typename... Args>
  String(T str, Args... args) : __string(
    string(str) + String(args...).__string
  ) { }
  template<typename... Args>
  String(int str, Args... args) : __string(
    to__string(str) + String(args...).__string
  ) { }
  // Prototype for stream insertion
  friend ostream&
    operator<<(
      ostream& os,
      const String& str) {
    os << str.__string;
    return os;
  }
  String toLowerCase()
  {
    String lower_case_str(*this);
    for (uint64_t i = 0; i < lower_case_str.length; i++)
    {
      if (lower_case_str.__string[i] >= 65 && lower_case_str.__string[i] <= 90)
      {
        lower_case_str.__string[i] += 32;
      }
    }
    return lower_case_str;
  }
  int64_t indexOf(String searchString, uint64_t initial_pos = 0, uint64_t last_pos = 0) {
    if (last_pos == 0)
      last_pos = length - searchString.length;
    do {
      bool isEqual = true;
      for (uint64_t i = 0; i < searchString.length; i++)
        if (__string[initial_pos + i] != searchString[i]) {
          isEqual = false;
          break;
        }
      if (isEqual)
        return initial_pos;
    } while (++initial_pos < last_pos);
    return -1;
  }
  String slice(uint64_t start = 0, int64_t end = 0) {
    if (end == 0)
      end = length;
    else if (end < 0) {
      end = length - end - 2;
      if (end < 0)
        end = 0;
    }
    return __string.substr(start, end - start);
  }
  vector<String> split(String separator) {
    vector<String> parts;
    uint64_t current_pos = 0;
    do {
      auto next_pos = this->indexOf(separator, current_pos);
      if (next_pos == -1)
        next_pos = length;
      string part = __string.substr(current_pos, next_pos);
      parts.push_back(part);
      current_pos += part.length() + separator.length;
    } while (current_pos < length);
    return parts;
  }
  // Operators
  bool operator==(
    const String& str
    ) {
    if (length != str.length)
      return false;
    else
      for (uint64_t i = 0; i < length; i++)
        if (__string[i] != str.__string[i])
          return false;
    return true;
  }
  void operator=(
    const String& str
    ) {
    __string = str.__string;
  }
  char& operator[] (uint64_t i) { return __string[i]; }
  friend bool operator<(
    const String& _Left, const String& _Right) noexcept {
    return _Left.__string.compare(_Right.__string) < 0;
  }
  String operator+(
    const string& src
    ) {
    return __string + src;
  }
  void operator+=(
    const String& src
    ) {
    __string += src.__string;
    __length = __string.length();
  }
};