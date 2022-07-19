#include "Array.hpp"
#include "String.hpp"
int main(int argc, char** argv) {
  {
    Array<char> list = { '1', '2' };
    for (auto item : list) {
      std::cout << item << std::endl;
    }
  }
  {
    Array<char*> list = { '1', '2' };
    for (char item : list) {
      std::cout << item << std::endl;
    }
  }
  {
    Array<char**> list = { "11", "22" };
    for (auto item : list) {
      std::cout << item << std::endl;
    }
  }
  {
    String str = "test";
    for (char c : str) {
      std::cout << c << std::endl;
    }
    std::cout << str << std::endl;
    std::cout << str.length << std::endl;
  }
  return 0;
}
