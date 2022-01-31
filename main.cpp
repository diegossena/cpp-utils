#include "http.hpp"
int main(int argc, char** argv) {
  auto data = http.get("grupojrb.com.br").data;
  cout << data;
  return 0;
}