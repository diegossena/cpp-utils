// #include "http.hpp"
#include "console.hpp"
#include "String.hpp"

int main(int argc, char** argv) {
  console.log(
    String(
      "GET",
      12,
      "213213",
      "sadsadas"
    )
  );
  return 0;
}
