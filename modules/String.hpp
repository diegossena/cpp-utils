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
  operator const char* () {
    return _string.c_str();
  }
  // with no arguments
  String() {}
  // Copy Constructor
  String(const string& str) : _string(str) {}
  String(const String& str) : _string(str._string) {}
  // with one arguments
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
    //cout << "end: " << end << endl;
    return _string.substr(start, end - start);
  }
  // Operators
  void operator=(
    const String& str
    ) {
    _string = str._string;
  }
  char& operator[] (uint64_t i) { return _string[i]; }
  String operator+(
    const String& src
    ) {
    return _string + src._string;
  }
  void operator+=(
    const String& src
    ) {
    _string += src._string;
    _length = _string.length();
  }
};
/*
class String
{
  // Props
  char* buffer_ = nullptr;
  uint64_t _length = 0;
  // Operators
  bool operator==(
    const String& str
    ) {
    if (_length != str.length)
      return false;
    else
      for (uint64_t i = 0; i < length; i++)
        if (buffer_[i] != str.buffer_[i])
          return false;
    return true;
  }
public:
  // refs
  const uint64_t& length = _length;
  // Conversion
  operator const char* () {
    return buffer_;
  }
  // with no arguments
  String() {}
  // Copy Constructor
  String(const String& source)
  {
    _length = source.length;
    buffer_ = new char[source.length + 1];
    for (uint64_t i = 0; i < length; i++)
      buffer_[i] = source.buffer_[i];
    buffer_[length] = '\0';
  }
  // with one arguments
  String(const char* str) {
    if (str != nullptr) {
      _length = 0;
      const char* ptr = str;
      while (*ptr++)
        _length++;
      buffer_ = new char[length + 1];
      strcpy(buffer_, str);
    }
  }
  ~String() {
    cout << "~String" << endl;
    delete[] buffer_;
  }
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
    substr._length = end - start;
    substr.buffer_ = new char[substr.length];
    for (uint64_t i = 0;start < end; start++, i++) {
      substr.buffer_[i] = buffer_[start];
    }
    return substr;
  }
  // Operators
  void operator=(
    const String* str
    ) {
    _length = str->length;
    buffer_ = str->buffer_;
    //const char* ptr = str->buffer_;
    //memcpy(buffer_, str->buffer_, length + 1);
  }
  void operator=(
    const String& str
    ) {
    _length = str.length;
    const char* ptr = str.buffer_;
    while (*ptr++)
      _length++;
    buffer_ = new char[length + 1];
    strcpy(buffer_, str.buffer_);
  }
  const char& operator[] (uint64_t i) { return buffer_[i]; }
  String operator+(
    const String& src
    ) {
    String str;
    str._length = length + src.length;
    str.buffer_ = new char[str._length];
    for (uint64_t i = 0; i < length; i++)
      str.buffer_[i] = buffer_[i];
    for (uint64_t i = 0; i < length; i++)
      str.buffer_[length + i] = src.buffer_[i];
    return str;
  }
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
};
*/
