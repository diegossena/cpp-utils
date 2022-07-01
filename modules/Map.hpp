#pragma once
// Global Headers
#include <map>
#include <initializer_list>
#include <string>
using namespace std;
// Definition
class Map {
  map<string, string> pairs;
public:
  Map() {}
  Map(initializer_list<pair<const string, string>> list) : pairs(list) {}
  string& operator[] (string key) { return pairs[key]; }
};