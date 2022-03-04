#pragma once
#include <string>
using namespace std;
#include "Error.hpp"
#include "Socket.hpp"
#include "String.hpp"
#define DEFAULT_HTTP_PORT 80U
class Http {
public:
  struct Response {
    string data, statusText;
    u_short status;
  };
private:
  Response request(string method, string host, string path = "/", u_short port = DEFAULT_HTTP_PORT, string body = "") {
    auto socket = Socket(host, port);
    string httpRequest = method
      + " "
      + path
      + " HTTP/1.1\r\nHost: "
      + host;
    if (port != 80U)
    {
      httpRequest += ":" + to_string(port);
    }
    httpRequest += "\r\nConnection: close\r\n\r\n" + body;
    socket.write(httpRequest);
    socket.read(9);
    // Parse response
    char buffer[BUFSIZ] = "", caracter, * ptr;
    Response response;
    // Get status.code
    response.status = atoi(socket.read(3).c_str());
    socket.readByte();
    // Get status.text
    while ((buffer[0] = socket.readByte()) != '\r') {
      response.statusText.push_back(buffer[0]);
    }
    socket.readByte();
    // Get headers
    map<string, string> headers;
    while (true) {
      ptr = buffer;
      *ptr = socket.readByte();
      if (*ptr == '\r')
        break;
      *ptr++;
      // get header key
      while (true) {
        caracter = socket.readByte();
        if (caracter == ':') {
          socket.readByte();
          break;
        }
        *ptr++ = caracter;
      }
      string key(String::toLowerCase(buffer));
      ptr = buffer;
      memset(buffer, '\0', BUFSIZ);
      // get header value
      while (true) {
        caracter = socket.readByte();
        if (caracter == '\r') {
          socket.readByte();
          break;
        }
        *ptr++ = caracter;
      }
      headers[key] = buffer;
      memset(buffer, '\0', BUFSIZ);
    }
    socket.readByte();
    int contentLength = atoi(headers["content-length"].c_str());
    response.data = socket.read(contentLength);
    return response;
  }
public:
  // Methods
  Response get(string host, string path = "/", u_short port = DEFAULT_HTTP_PORT)
  {
    return request("GET", host, path, port);
  }
} http;
