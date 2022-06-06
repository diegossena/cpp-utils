#pragma once
#include <iostream>
#include <vector>
#include <tchar.h>
using namespace std;
class String {
  string _string;
  uint64_t _length = _string.length();
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
  uint64_t indexOf(String searchString, uint64_t position = 0) {
    const uint64_t lastIndex = length - searchString.length;
    do {
      bool isEqual = true;
      for (uint64_t i = 0; i < lastIndex; i++)
        if (_string[position + i] != searchString[i]) {
          isEqual = false;
          break;
        }
      if (isEqual)
        return position;
    } while (position++ < length);
    return -1;
  }
  String slice(uint64_t start = 0, long long end = 0) {
    if (end == 0)
      end = length;
    else if (end < 0) {
      end = length - end - 2;
      if (end < 0)
        end = 0;
    }
    return _string.substr(start, end - start);
  }
  // Operators
  void operator=(
    const String& str
    ) {
    _string = str._string;
  }
  char& operator[] (uint64_t i) { return _string[i]; }
  friend bool operator<(
    const string& _Left, const string& _Right) noexcept {
    return _Left.compare(_Right) < 0;
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