#include "index.hpp"
namespace Console {
  void backspace(int spaces) {
    int i;
    for (i = 0; i < spaces; i++) {
      cout << "\b";
    }
    for (i = 0; i < spaces; i++) {
      cout << " ";
    }
    for (i = 0; i < spaces; i++) {
      cout << "\b";
    }
  }
}