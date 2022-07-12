#pragma once
// Global Headers
#include <map>
#include <initializer_list>
using namespace std;
#include "String.hpp"
// Definition
class Map {
  map<String, String> pairs;
public:
  Map() {}
  Map(initializer_list<pair<const String, String>> list) : pairs(list) {}
  String& operator[] (String key) { return pairs[key]; }
};