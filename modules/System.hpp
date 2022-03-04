#include "index.hpp"
namespace System {
  string exec(string cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw runtime_error("popen() failed!");
    char buffer[BUFSIZ];
    string result;
    try {
      while (fgets(buffer, BUFSIZ, pipe) != NULL) {
        result += buffer;
      }
    }
    catch (...) {
      pclose(pipe);
      throw;
    }
    pclose(pipe);
    return result;
  }
}