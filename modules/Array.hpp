#pragma once
#include <cstdint>
#include <new>
#include <initializer_list>
using namespace std;
#include "Object.hpp"
#include "Iterator.hpp"
#include "String.hpp"
template <class T>
class Array : public Object {
  T** __list = undefined;
  uint64_t __length = 0;
public:
  // refs
  const uint64_t& length = __length;
  // constructors
  Array() {}
  Array(uint64_t length) : __list(new T* [length]), __length(length) {
    uint64_t i = __length;
    do __list[i] = undefined; while (i--);
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
  // methods
  uint64_t push(T item) {
    uint64_t new_length = __length + 1;
    T** new_list = new T * [new_length];
    memcpy(new_list, __list, sizeof(T**) * __length);
    delete[]__list;
    new_list[__length] = new T(item);
    __list = new_list;
    __length = new_length;
    return new_length;
  }
  const char* toString() {
    String str = '[';
    for (T& i : *this) {
      if (&i != __list[0])
        str += ", ";
      str += i;
    }
    str += ']';
    return str;
  }
  // operators
  using ArrayIterator = PointerIterator<T>;
  ArrayIterator begin() { return ArrayIterator(__list); }
  ArrayIterator end() { return ArrayIterator((T**)(__list + __length)); }
  T& operator[] (uint64_t i) {
    return *__list[i];
  }
};