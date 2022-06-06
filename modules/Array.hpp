#pragma once
#include <vector>
#include <memory>
using namespace std;
template <class T>
class Array {
  vector<unique_ptr<T>> items;
  uint64_t _length = 0;
  //
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
  //
public:
  // Refs
  const uint64_t& length = _length;
  // Constructors
  Array(uint64_t arrayLength) : items(arrayLength), _length(arrayLength) {}
  Array(std::initializer_list<T> elements) : items(elements.size()), _length(elements.size()) {
    for (auto i = 0; i != elements.size(); i++) {
      items[i] = make_unique<T>(*(elements.begin() + i));
    }
  }
  // Methods
  void push(T item) { items.push_back(make_unique<T>(item)); _length++; }
  T pop() {
    _length--;
    T item = *items.back();
    items.pop_back();
    return item;
  }
  // Operators
  bool operator!=(
    const Array& arr
    ) {
    return items[0] != arr[0];
  }
  T& operator[] (uint64_t i) { return *items[i]; }
  Iterator begin() {
    return items.begin();
  }
  Iterator end() {
    return items.end();
  }
};