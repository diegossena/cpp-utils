#include <iostream>
#include <vector>
#include <memory>
using namespace std;
#include "String.hpp"
#include "Date.hpp"
#include "Array.hpp"
int main(int argc, char** argv) {
  String text = "Hello World";
  cout << text.slice(1) << endl;
  cout << text.slice(0, -1).length << endl;
}