#pragma once
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
using namespace std;
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
  // log overloads
  void log() {
    cout << endl;
  }
  void log(bool data) {
    cout << "true" << endl;
  }
  template <typename T>
  void log(T data) {
    cout << data << endl;
  }
  template<typename... Args>
  void log(bool data, Args... args) {
    cout << "true" << " ";
    log(args...);
  }
  template<typename T, typename... Args>
  void log(T data, Args... args) {
    cout << data << " ";
    log(args...);
  }
} console;