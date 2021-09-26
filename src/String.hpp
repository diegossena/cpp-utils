#include "index.hpp"
namespace String {
  string toLowerCase(string str) {
    for (int i = 0; i < str.length(); i++) {
      if (str[i] >= 65 && str[i] <= 90) {
        str[i] += 32;
      }
    }
    return str;
  }
  vector<string> split(string str, string separator) {
    std::vector<string> result;
    char* ptr = strtok((char*)str.c_str(), separator.c_str());
    while (ptr != NULL) {
      result.push_back(ptr);
      ptr = strtok(NULL, separator.c_str());
    }
    return result;
  }
}