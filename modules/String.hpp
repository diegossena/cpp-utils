#pragma once
#include <iostream>
#include <vector>
#include <tchar.h>
using namespace std;
class String
{
  // Props
  char* buffer_ = nullptr;
  uint64_t length_ = 0;
  // Operators
  bool operator==(
    const String& str
    ) {
    if (length_ != str.length)
      return false;
    else
      for (uint64_t i = 0; i < length; i++)
        if (buffer_[i] != str.buffer_[i])
          return false;
    return true;
  }
  void operator=(
    const String& str
    ) {
    buffer_ = str.buffer_;
    length_ = str.length;
  }
public:
  // refs
  const uint64_t& length = length_;
  // Conversion
  operator const char* () {
    return buffer_;
  }
  // with no arguments
  String() {}
  // Copy Constructor
  String(const String& source)
  {
    length_ = source.length;
    buffer_ = new char[source.length + 1];
    for (uint64_t i = 0; i < length; i++)
      buffer_[i] = source.buffer_[i];
    buffer_[length] = '\0';
  }
  // with one arguments
  String(const char* str) {
    if (str != nullptr) {
      length_ = 0;
      const char* ptr = str;
      while (*ptr++)
        length_++;
      buffer_ = new char[length + 1];
      for (uint64_t i = 0; i < length_; i++)
        buffer_[i] = str[i];
      buffer_[length] = '\0';
    }
  }
  ~String() { delete[] buffer_; }
  // Prototype for stream insertion
  friend ostream&
    operator<<(
      ostream& os,
      const String& str) {
    for (int i = 0; i < str.length; i++)
    {
      os << str.buffer_[i];
    }
    return os;
  }
  String toLowerCase()
  {
    String lower_case_str(*this);
    for (uint64_t i = 0; i < lower_case_str.length; i++)
    {
      if (lower_case_str.buffer_[i] >= 65 && lower_case_str.buffer_[i] <= 90)
      {
        lower_case_str.buffer_[i] += 32;
      }
    }
    return lower_case_str;
  }
  uint64_t indexOf(String searchString, uint64_t position = 0) {
    const uint64_t lastIndex = length - searchString.length;
    do {
      bool isEqual = true;
      for (uint64_t i = 0; i < lastIndex; i++)
        if (buffer_[position + i] != searchString[i]) {
          isEqual = false;
          break;
        }
      if (isEqual)
        return position;
    } while (position++ < length);
    return -1;
  }
  String slice(uint64_t start = 0, long long end = -1) {
    String substr;
    if (end > length)
      end = length;
    else if (end < 0) {
      end = length - end;
      if (end < 0)
        end = 0;
    }
    substr.length_ = end - start;
    substr.buffer_ = new char[substr.length];
    for (uint64_t i = 0;start < end; start++, i++) {
      substr.buffer_[i] = buffer_[start];
    }
    return substr;
  }
  // Operators
  const char& operator[] (uint64_t i) { return buffer_[i]; }
  String operator+(
    const String& src
    ) {
    String str;
    str.length_ = length + src.length;
    str.buffer_ = new char[str.length_];
    for (uint64_t i = 0; i < length; i++)
      str.buffer_[i] = buffer_[i];
    for (uint64_t i = 0; i < length; i++)
      str.buffer_[length + i] = src.buffer_[i];
    return str;
  }
  /*
  vector<String> split(String separator) {
    vector<String> parts;
    uint64_t current_pos = 0;
    std::string token;
    while (current_pos < length) {
      uint64_t next_pos = this->indexOf(separator);
      token = s.substr(0, pos);
      std::cout << token << std::endl;
      s.erase(0, pos + delimiter.length());
    }
    std::cout << s << std::endl;
    return parts
  }
  */
};