// #include "console.hpp"
// #include "Array.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
//#include "String.hpp"

int main(int argc, char** argv) {
  //Array<unsigned char> list1 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
  //Array_UniquePtr<unsigned char> list2 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

  // std::string txt2 = { 'a', 'b' };
  // printf("%u\n", &txt2[0]);
  // for (int i = 0; i < 1000; i++) {
  //   txt2 += "ab";
  // }
  // printf("%u %u %u\n", &txt2[0], &txt2[988], &txt2[0] + 988);

  std::vector<char> list = { 'a', 'b' };
  printf("%u\n", &list[0]);
  for (int i = 0; i < 1000; i++) {
    list.push_back('a');
  }
  printf("%u %u %u\n", &list[0], &list[988], &list[0] + 988);
  return 0;
}
