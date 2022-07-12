#pragma once
#include <iostream>
using namespace std;
class String {
  const char* __string = "";
  uint64_t __length = 0;
public:
  // refs
  const size_t& length = __length;
  String() {
    __string = (char*)malloc(10);
  }
};