#pragma once
// Global Headers
#include <string>
using namespace std;
// Local Headers
#include "Socket.hpp"
#include "Map.hpp"
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
  class RequestConfig {
  public:
    URL url = "";
    String method = "GET", data = "";
    RequestConfig setURL(URL _url) {
      url = _url;
      return *this;
    }
    RequestConfig setMethod(String _method) {
      method = _method;
      return *this;
    }
    RequestConfig setData(String _data) {
      data = _data;
      return *this;
    }
    static RequestConfig URL(URL _url) {
      return RequestConfig().setURL(_url);
    }
  };
  // Methods
  Response request(RequestConfig config) {
    if (!config.url.port)
      config.url.port = 80;
    auto socket = Socket(config.url.host, config.url.port);
    String httpRequest = config.method
      + " "
      + config.url.path
      + " HTTP/1.1\r\nHost: " + config.url.host
      + (config.url.port == 80 ? "" : ":" + to_string(config.url.port))
      + "\r\nConnection: close\r\n\r\n"
      + config.data;
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
    int contentLength = atoi(headers["content-length"]);
    response.data = socket.read(contentLength);
    return response;
  }
  Response get(URL url) {
    auto config = RequestConfig::URL(url);
    return request(config);
  }
} http;
