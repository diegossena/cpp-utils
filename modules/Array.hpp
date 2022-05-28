#pragma once
#include <vector>
#include <memory>
using namespace std;
template <class T>
class Array {
  vector<unique_ptr<T>> items;
  uint64_t _length = 0;
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
  typename vector<T>::iterator begin() { return items.begin(); };
  typename vector<T>::iterator end() { return items.end(); };
  bool operator!=(
    const Array& arr
    ) {
    return items[0] != arr[0];
  }
  T& operator[] (uint64_t i) { return *items[i]; }
};
/*
template <class T>
class Array {
  T* items;
  uint64_t _length = items.size();
public:
  // Refs
  const uint64_t& length = _length;
  // Constructors
  Array(uint64_t arrayLength) : items(new T[arrayLength]), _length(arrayLength) {}
  Array(std::initializer_list<T> elements) : items(new T[elements.size()]), _length(elements.size()) {
    auto element_ptr = elements.begin();
    for (auto i = 0; i != elements.size(); i++) {
      items[i] = new T(*element_ptr++);
    }
  }
  ~Array() { delete[] items; }
  // Methods
  void push(T item) {
    T* new_arr = new T[++_length];
    for (uint64_t i = 0; i < _length; i++) {
      new_arr[i] = items[i];
      cout << items[i] << endl;
    }
    //memcpy(new_arr, items, _length);
    delete[] items;
    items = new_arr;
    items[_length] = new T(item);
  }
  T pop() {
    _length--;
    T item = items.back();
    items.pop_back();
    return item;
  }
  // Operators
  typename vector<T>::iterator begin() { return items.begin(); };
  typename vector<T>::iterator end() { return items.end(); };
  bool operator!=(
    const Array& arr
    ) {
    return items[0] != arr[0];
  }
  T& operator[] (uint64_t i) { return items[i]; }
};
*/