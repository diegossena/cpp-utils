#pragma once
// #include <iterator>
// using namespace std;
template <class T>
class Iterator {
protected:
  // using iterator_category = std::forward_iterator_tag;
  // using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  pointer __ptr;
public:
  // Iterator(pointer ptr) : __ptr(ptr) {}
  Iterator(pointer ptr) : __ptr(ptr) {}
  virtual reference operator*() const { return *__ptr; }
  Iterator& operator++() { __ptr++; return *this; }
  friend bool operator!= (const Iterator& a, const Iterator& b) { return a.__ptr != b.__ptr; };
};
template <class T>
class PointerIterator : public Iterator<T> {
  using BaseIterator = Iterator<T>;
  using BaseIterator::Iterator;
  using BaseIterator::__ptr;
  using reference = T&;
  using pointer = T*;
public:
  reference operator*() const { return *(pointer)*__ptr; }
};