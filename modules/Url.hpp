#pragma once
#include "String.hpp"
using namespace std;
class URL
{
public:
  u_short port = 0;
  String protocol, host, path = "/";
  URL(String input) {
    if (!input.length)
      return;
    auto protocolEnd = input.indexOf("://");
    if (protocolEnd != -1) {
      protocol = input.slice(0, protocolEnd);
      protocolEnd += 3;
    }
    else
      protocolEnd = 0;
    auto hostStart = protocolEnd;
    auto pathStart = input.indexOf("/", hostStart);
    if (pathStart == -1)
      pathStart = input.length;
    auto origin = input.slice(hostStart, pathStart).split(":");
    host = origin[0];
    if (origin[1])
      port = atoi(origin[1]);
    path = input.slice(pathStart);
    if (!path)
      path = "/";
  }
  URL(const char* input) : URL(String(input)) { }
};
