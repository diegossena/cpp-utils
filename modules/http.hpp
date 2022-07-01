#pragma once
// Global Headers
#include <string>
using namespace std;
// Local Headers
#include "Map.hpp"
#include "Socket.hpp"
#include "Error.hpp"
#include "String.hpp"
#include "URL.hpp"
// Definitions
#define DEFAULT_HTTP_PORT 80U
class Http {
public:
  struct Response {
    String data, statusText;
    u_short status;
  };
  struct RequestConfig {
    String url, method = "GET", data = "";
  };
  // Methods
  Response request(RequestConfig config) {
    URL url(config.url);
    auto socket = Socket(url.host, url.port);
    String httpRequest = config.method
      + " "
      + url.path
      + " HTTP/1.1\r\nHost: "
      + url.host;
    if (url.port != 80)
      httpRequest += ":" + to_string(url.port);
    httpRequest += "\r\nConnection: close\r\n\r\n" + config.data;
    console.log(httpRequest);
    socket.write(httpRequest);
    socket.read(9);
    // Parse response
    char buffer[BUFSIZ] = "", caracter, * ptr;
    Response response;
    response.status = atoi(socket.read(3).c_str());
    socket.readByte();
    // Get status.text
    while ((buffer[0] = socket.readByte()) != '\r') {
      response.statusText += buffer[0];
    }
    socket.readByte();
    // Get headers
    Map headers;
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
      string key = String(buffer).toLowerCase();
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
  Response get(String url) {
    RequestConfig config;
    config.url = url;
    return request(config);
  }
} http;
