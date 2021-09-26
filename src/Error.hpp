#include "index.hpp"
map<int, string> errorCodes = {
  { ETIMEDOUT, "ETIMEDOUT" },
  { EFAULT, "EFAULT" }
};
class Error {
public:
  int errnum;
  string code;
  string syscall;
  // If present, error.address is a string describing the address to which a network connection failed.
  string address;
  // If present, error.port is the network connection port that is not available.
  int port;
  // Methods
  void what() {
    cout
      << "{ syscall: '" << syscall
      << "', code: '" << code
      << "', errno: " << errnum
      << " }";
  }
  // Constructors
  Error() {}
  Error(string syscall, int errnum) : errnum(errnum), syscall(syscall) {
    string currentCode = errorCodes[errnum];
    code = currentCode.empty() ? "INESPERED" : errorCodes[errnum];
  }
};