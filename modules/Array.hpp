#pragma once
#include <cstdint>
#include <new>
#include <initializer_list>
using namespace std;
#include "Iterator.hpp"
template <class T>
class Array {
  T** __list = nullptr;
  uint64_t __length = 0;
public:
  // refs
  const uint64_t& length = __length;
  // constructors
  Array() {}
  Array(uint64_t length) : __list(new T* [length]), __length(length) {
    uint64_t i = __length;
    do __list[i] = nullptr; while (i--);
  }
  Array(initializer_list<T> list) : __list(new T* [list.size()]), __length(list.size()) {
    uint64_t i = __length;
    while (i--)
      __list[i] = new T(*(list.begin() + i));
  }
  ~Array() {
    if (__length) {
      uint64_t i = __length;
      while (i--)
        delete __list[i];
      delete[] __list;
    }
  }
  using ArrayIterator = PointerIterator<T*>;
  ArrayIterator begin() { return ArrayIterator(__list); }
  ArrayIterator end() { return ArrayIterator((T**)(__list + __length)); }
  T& operator[] (uint64_t i) { return *__list[i]; }
};