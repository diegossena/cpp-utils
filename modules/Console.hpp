#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
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
  // log overloads
  void log() {
    cout << endl;
  }
  /*
  #if 'ç' == 50087
    void log(const char* data) {
      const char* ptr = data;
      cout << endl;
    }

    template<typename... Args>
    void log(const char* data, Args... args) {
      const char* ptr = data;
      while (*ptr != '\0') {
        cout << *ptr++;
      }
      cout << " ";
      log(args...);
    }
  #else
  */
  void log(const char* data) {
    const char* ptr = data;
    while (*ptr != '\0') {
      cout << *ptr++;
    }
    cout << endl;
  }

  template<typename... Args>
  void log(const char* data, Args... args) {
    const char* ptr = data;
    while (*ptr != '\0') {
      cout << *ptr++;
    }
    cout << " ";
    log(args...);
  }
  //#endif
  // bool
  void log(bool data) {
    cout << (data ? "true" : "false") << endl;
  }
  template<typename... Args>
  void log(bool data, Args... args) {
    cout << (data ? "true" : "false") << " ";
    log(args...);
  }
  // others
  template <typename T>
  void log(T data) {
    cout << data << endl;
  }
  template<typename T, typename... Args>
  void log(T data, Args... args) {
    cout << data << " ";
    log(args...);
  }
} console;