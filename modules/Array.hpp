#pragma once
#include <variant>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
using namespace std;
#include "Object.hpp"
template <typename T>
class Array : public Object {
  using Iterator = typename vector<T>::iterator;
protected:
  vector<T> _items = {};
  uint64_t _length = 0;
public:
  // Constructors
  Array(uint64_t length) : _items(length), _length(length) {}
  Array(std::initializer_list<T> elements)
    : _items(elements),
    _length(elements.size()) {}
  // Methods
  Iterator begin() { return _items.begin(); }
  Iterator end() { return _items.end(); }
  // Operators
  T& operator[] (uint64_t i) { return _items[i]; }
  const string toString() {
    stringstream str;
    str << "[";
    for (auto& item : _items) {
      if (item == _items[0])
        str << item;
      else
        str << ", " << item;
    }
    str << "]";
    return str.str();
  }
};

template <typename T>
class Array_UniquePtr : public Array<unique_ptr<T>> {
  using BaseArray = Array<unique_ptr<T>>;
  using BaseArray::_items;
  using VectorIterator = typename vector<unique_ptr<T>>::iterator;
  class Iterator : public VectorIterator {
  public:
    using pointer = T*;
    using reference = T&;
    // Constructors
    Iterator(const VectorIterator& vector_iterator) : VectorIterator(vector_iterator) {}
    // Operators
    pointer operator->() const { return this->VectorIterator::operator*().get(); }
    reference operator*() const { return *(this->VectorIterator::operator*()); }
    reference operator[](size_t n) const {
      return *(this->VectorIterator::operator[](n));
    }
  };
public:
  Array_UniquePtr(std::initializer_list<T> elements)
    : BaseArray(elements.size())
  {
    for (auto i = 0; i != elements.size(); i++)
      _items[i] = make_unique<T>(*(elements.begin() + i));
  }
  // Methods
  Iterator begin() {
    return _items.begin();
  }
  Iterator end() {
    return _items.end();
  }
  // Operators
  T& operator[] (uint64_t i) { return *_items[i]; }
};