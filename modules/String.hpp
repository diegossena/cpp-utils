#pragma once
#include <iostream>
#include <vector>
using namespace std;
class String
{
  // Props
  char* buffer = nullptr;
  size_t length_ = 0;
  // Operators
  bool operator==(
    const String& str
    ) {
    if (length_ != str.length) {
      return false;
    }
    else {
      for (size_t i = 0; i < length_; i++)
        if (buffer[i] != str.buffer[i])
          return false;
    }
    return true;
  }
  void operator=(
    const String& str
    ) {
    buffer = str.buffer;
    length_ = str.length;
  }
public:
  // refs
  const size_t& length = length_;
  // with no arguments
  String() {}
  // Copy Constructor
  String(const String& source)
  {
    length_ = source.length;
    buffer = new char[source.length];
    for (size_t i = 0; i < length; i++)
      buffer[i] = source.buffer[i];
  }
  // with one arguments
  String(const char* str) {
    if (str != nullptr) {
      length_ = 0;
      const char* ptr = str;
      while (*ptr++)
        length_++;
      buffer = new char[length_];
      for (size_t i = 0; i < length_; i++)
        buffer[i] = str[i];
    }
  }
  ~String() { delete[] buffer; }
  // Prototype for stream insertion
  friend ostream&
    operator<<(
      ostream& os,
      const String& str) {
    for (int i = 0; i < str.length; i++)
    {
      os << str.buffer[i];
    }
    return os;
  }
  String toLowerCase()
  {
    String lower_case_str(*this);
    for (size_t i = 0; i < lower_case_str.length; i++)
    {
      if (lower_case_str.buffer[i] >= 65 && lower_case_str.buffer[i] <= 90)
      {
        lower_case_str.buffer[i] += 32;
      }
    }
    return lower_case_str;
  }
  size_t indexOf(String searchString, size_t position = 0) {
    do {
      if (buffer[position] == searchString[0]) {
        bool isEqual = true;
        for (size_t i = 1; i < searchString.length; i++)
          if (buffer[position + i] != searchString[i]) {
            isEqual = false;
            break;
          }
        if (isEqual)
          return position;
      }
      position++;
    } while (position < length);
    return -1;
  }
  String slice(size_t start = 0, long long end = -1) {
    String substr;
    if (end > length)
      end = length;
    else if (end < 0) {
      end = length - end;
      if (end < 0)
        end = 0;
    }
    substr.length_ = end - start;
    substr.buffer = new char[substr.length];
    for (size_t i = 0;start < end; start++, i++) {
      substr.buffer[i] = buffer[start];
    }
    return substr;
  }
  const char& operator[] (size_t i) { return buffer[i]; }
  /*
  vector<String> split(String separator) {
    vector<String> parts;
    size_t current_pos = 0;
    std::string token;
    while (current_pos < length) {
      size_t next_pos = this->indexOf(separator);
      token = s.substr(0, pos);
      std::cout << token << std::endl;
      s.erase(0, pos + delimiter.length());
    }
    std::cout << s << std::endl;
    return parts
  }
  */
};