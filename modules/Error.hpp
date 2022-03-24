#pragma once
#include <iostream>
#include <string>
#include <map>
#include <errno.h>
#include <exception>
#include <windows.h>
using namespace std;
map<int, string> errorCodes = {
  { ETIMEDOUT, "ETIMEDOUT" },
  { EFAULT, "EFAULT" },
  { WSAENOTSOCK, "WSAENOTSOCK" },
  { }
};
/*
Error(string syscall, int errnum)
*/
class Error : public exception {
public:
  int errnum;
  string code;
  string syscall;
  // If present, error.address is a string describing the address to which a network connection failed.
  string address;
  // If present, error.port is the network connection port that is not available.
  int port;
  // Methods
  virtual const char* what() const throw() {
    string message = "{ syscall: '" + syscall
      + "', code: '" + code
      + "', errno: " + to_string(errnum)
      + " }";
    return message.c_str();
  }
  // Constructors
  Error(string syscall, int errnum) : errnum(errnum), syscall(syscall) {
    string currentCode = errorCodes[errnum];
    code = currentCode.empty() ? "INESPERED" : errorCodes[errnum];
    throw* this;
  }
};
