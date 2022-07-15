#pragma once
#include <iterator>
#include <type_traits>
using namespace std;
template <typename T>
class Iterator {
protected:
  T* __ptr;
public:
  Iterator(T* ptr) : __ptr(ptr) { }
  T& operator*() const { return *__ptr; }
  Iterator& operator++() { __ptr++; return *this; }
  friend bool operator!= (const Iterator& a, const Iterator& b) { return a.__ptr != b.__ptr; };
};
template <typename T>
class PointerIterator : public Iterator<T*> {
  using Iterator<T*>::Iterator;
  using Iterator<T*>::__ptr;
public:
  T& operator*() const { return *(*__ptr); }
};