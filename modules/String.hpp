#pragma once
#include <cstdint>
#include <cstring>
class String {
  char* __string;
  uint64_t __length = 0;
public:
  // refs
  const uint64_t& length = __length;
  // conversions
  operator const char* () { return __string; }
  // constructors
  String(const char* str) : __length(strlen(str)) {
    uint64_t size = __length + 1;
    __string = (char*)memcpy(malloc(size), str, size);
  }
  ~String() { free(__string); }
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
  //
};