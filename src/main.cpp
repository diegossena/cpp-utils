#include "Array.hpp"
#include "String.hpp"
#include "console.hpp"
using namespace std;
int main(int argc, char** argv) {
  cout << "test" << endl;
  Array<const char*> test = { "a", "b" };
  return 0;
}
