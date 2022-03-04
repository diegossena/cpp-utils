#include <iostream>
#include "String.hpp"
//#include "http.hpp"
int main(int argc, char** argv) {
  String test = "1fASDASFSAF31@$23";
  String test2 = test;
  cout << test2.slice(0, 200).length << '\n';
  return 0;
}