#pragma once
#include <iostream>
#include <cstdint>
#include <new>
#include <initializer_list>
#include <type_traits>
#include <cstring>
//#include "String.hpp"
#define undefined nullptr
#define ARRAY_DEBUG true
// #if ARRAY_DEBUG
//     cout
//       << "Array(initializer_list<T*> list){"
//       << "__length=" << __length << "}"
//       << endl;
// #endif
template <typename T>
class Array {
  typedef std::remove_pointer<T>::type TT;
protected:
  T* __list = undefined;
  uint64_t __length = 0;
  class Iterator {
    T* __ptr;
  public:
    Iterator(T* ptr) : __ptr(ptr) { }
    T& operator*() const { return *__ptr; }
    Iterator& operator++() { __ptr++; return *this; }
    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.__ptr != b.__ptr; };
  };
public:
  // refs
  const uint64_t& length = __length;
  // constructors
  Array(uint64_t length) : __list(new T[length]), __length(length) {
#if ARRAY_DEBUG
    std::cout
      << "Array(uint64_t length){"
      << "__length=" << __length << "}"
      << std::endl;
#endif
  }
  Array(std::initializer_list<TT> list) : __list(new T[list.size()]), __length(list.size()) {
#if ARRAY_DEBUG
    std::cout
      << "Array(std::initializer_list<T> list){"
      << "__length=" << __length << "}"
      << std::endl;
#endif
    uint64_t i = __length;
    while (i--) {
      if constexpr (std::is_pointer<T>::value) {
        __list[i] = new TT(*(list.begin() + i));
      }
      else {
        __list[i] = *(list.begin() + i);
      }
    }
  }
  ~Array() {
#if ARRAY_DEBUG
    std::cout << "~Array" << std::endl;
#endif
    delete[] __list;
  }
  // operators
  TT& operator[] (uint64_t i) {
    return *__list[i];
  }
  Iterator begin() { return Iterator((T*)__list); }
  Iterator end() { return Iterator(__list + __length); }
};