#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
#include "Array.hpp"
/**
 * "ascii"
 * "utf8" = 65501
 * "utf16le"
 * "ucs2"
 * "base64"
 * "latin1" = 850
 * "binary"
 * "hex"
*/
class Console {
public:
  void backspace(int spaces) {
    int i;
    for (i = 0; i < spaces; i++)
      cout << "\b";
    for (i = 0; i < spaces; i++)
      cout << " ";
    for (i = 0; i < spaces; i++)
      cout << "\b";
  }
  char getChar() {
    return _getch();
  }
  // methods
  void log() {
    cout << endl;
  }
  template<typename... Args>
  void log(int data, Args... args) {
    cout << data << " ";
    log(args...);
  }
  template<typename... Args>
  void log(const char* data, Args... args) {
    cout << data << " ";
    log(args...);
  }
  template<typename... Args>
  void log(bool data, Args... args) {
    cout << (data ? "true" : "false") << " ";
    log(args...);
  }
  template<typename T, typename... Args>
  void log(T& data, Args... args) {
    cout << data << " ";
    log(args...);
  }
} console;