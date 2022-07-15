#pragma once
#include <iostream>
#include <cstdint>
#include <new>
#include <initializer_list>
#include <type_traits>

#include "Object.hpp"
#include "Iterator.hpp"
#include "String.hpp"

#define ARRAY_DEBUG true
// #if ARRAY_DEBUG
//     cout
//       << "Array(initializer_list<T*> list){"
//       << "__length=" << __length << "}"
//       << endl;
// #endif
template <typename T>
class Array : public Object {
  T* __list = undefined;
  uint64_t __length = 0;
public:
  // refs
  const uint64_t& length = __length;
  // constructors
  Array() {}
  Array(uint64_t length) : __list(new T[length]), __length(length) {
    uint64_t i = __length;
    do __list[i] = undefined; while (i--);
  }
  // Array(std::initializer_list<const T> list) : __list(new T[list.size()]), __length(list.size()) {
  //   uint64_t i = __length;

  //   while (i--)
  //     if constexpr (std::is_pointer<T>::value)
  //       __list[i] = new std::remove_pointer<T>(*(list.begin() + i));
  //     else
  //       __list[i] = *(list.begin() + i);
  // }
  Array(std::initializer_list<T> list) : __list(new T[list.size()]), __length(list.size()) {
    uint64_t i = __length;

    while (i--)
      if constexpr (std::is_pointer<T>::value)
        __list[i] = new std::remove_pointer<T>(*(list.begin() + i));
      else
        __list[i] = *(list.begin() + i);
  }
  //
  ~Array() {
    if (__length) {
      uint64_t i = __length;
      if constexpr (is_pointer<T>::value)
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
    delete[] __list;
    new_list[__length] = new T(item);
    __list = new_list;
    __length = new_length;
    return new_length;
  }
  //operators
  friend std::ostream&
    operator<<(
      ostream& os,
      const Array<T>& arr) {
    uint64_t i = 0;
    os << '[';
    const char* wrapper =
      typeid(T) == typeid(String)
      ? "\""
      : typeid(T) == typeid(char)
      ? "'"
      : "";
    while (i < arr.__length) {
      if (i)
        os << ", ";
      os << wrapper << *arr.__list[i++] << wrapper;
    }
    os << ']';
    return os;
  }
  T& operator[] (uint64_t i) {
    if constexpr (is_pointer<T>::value)
      return *__list[i];
    else
      return __list[i];
  }
  //
  using ArrayIterator = PointerIterator<T>;
  ArrayIterator begin() { return ArrayIterator(__list); }
  ArrayIterator end() { return ArrayIterator((T**)(__list + __length)); }
};
// template <typename T>
// class Array<const T> {
//   T __list = undefined;
//   uint64_t __length = 0;
// public:
//   Array(T list) : __list(list), __length(0) {}
// };