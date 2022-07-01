#pragma once
#include <iostream>
#include <vector>
#include <tchar.h>
using namespace std;
class String {
  string _string;
  uint64_t _length = _string.length();
public:
  // refs
  const size_t& length = _length;
  // Conversion
  operator std::string() {
    return _string;
  }
  operator const char* () {
    return _string.c_str();
  }
  // with no arguments
  String() {}
  // Copy Constructor
  String(const string str) : _string(str) {}
  String(const String& str) : _string(str._string) {}
  String(char str) : _string(1, str) {}
  String(const char* str) : _string(str) {}
  // Prototype for stream insertion
  friend ostream&
    operator<<(
      ostream& os,
      const String& str) {
    os << str._string;
    return os;
  }
  String toLowerCase()
  {
    String lower_case_str(*this);
    for (uint64_t i = 0; i < lower_case_str.length; i++)
    {
      if (lower_case_str._string[i] >= 65 && lower_case_str._string[i] <= 90)
      {
        lower_case_str._string[i] += 32;
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
        if (_string[initial_pos + i] != searchString[i]) {
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
    return _string.substr(start, end - start);
  }
  vector<String> split(String separator) {
    vector<String> parts;
    uint64_t current_pos = 0;
    while (current_pos < length) {
      uint64_t next_pos = this->indexOf(separator, current_pos);
      string part = _string.substr(current_pos, next_pos);
      parts.push_back(part);
      current_pos += part.length() + separator.length;
    }
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
        if (_string[i] != str._string[i])
          return false;
    return true;
  }
  void operator=(
    const String& str
    ) {
    _string = str._string;
  }
  char& operator[] (uint64_t i) { return _string[i]; }
  friend bool operator<(
    const String& _Left, const String& _Right) noexcept {
    return _Left._string.compare(_Right._string) < 0;
  }
  String operator+(
    const String& src
    ) {
    return _string + src._string;
  }
  String operator+(
    const char* src
    ) {
    return _string + src;
  }
  void operator+=(
    const String& src
    ) {
    _string += src._string;
    _length = _string.length();
  }
};