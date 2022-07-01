#include "console.hpp"
#include "URL.hpp"
#include "http.hpp"

int main(int argc, char** argv) {
  http.get("localhost");
}
