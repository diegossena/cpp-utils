#pragma once
#include "String.hpp"
using namespace std;
class URL
{
public:
  unsigned short port = 0;
  String protocol, host, path = "/";
  URL(String input) {
    if (!input.length)
      return;
    int64_t uriEnd = input.length - 1;
    // get query start
    int64_t queryStart = input.indexOf("?");
    // protocol
    int64_t protocolEnd = input.indexOf("://");
    if (protocolEnd != -1) {
      protocol = input.slice(0, protocolEnd);
      protocolEnd += 3;
    }
    else
      protocolEnd = 0;

    // host
    int64_t hostStart = protocolEnd;
    int64_t pathStart = input.indexOf("/", hostStart);
    auto origin = input.slice(hostStart, pathStart).split(":");
    host = origin[0];
    if (origin[1])
      port = atoi(origin[1]);
    path = input.slice(pathStart);
  }
};
