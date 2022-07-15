#include "Array.hpp"
#include "String.hpp"
#include "console.hpp"
using namespace std;
int main(int argc, char** argv) {
  Array<char> test = { 'a', 'b', 'c' };
  console.log(test);
  return 0;
}
