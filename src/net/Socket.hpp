#include "index.hpp"
#define MAX_HTTP_BYTES 1001654
class WinSock2
{
public:
  WinSock2() {
    // Inicialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
      cerr << "Fail Inicialize Winsock\n";
      exit(1);
    }
  }
  ~WinSock2() {
    WSACleanup();
  }
} WinSock2;
namespace net {
  class Socket {
    SOCKET createdSocket;
    long int timeout_ms = 0;
  public:
    Socket& setTimeout(unsigned miliseconds) {
      timeout_ms = miliseconds * 1000;
      return *this;
    }
    Socket& createConnection(string host, u_short port) {
      int iResult;
      // Create a Socket Object
      closesocket(createdSocket);
      createdSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (createdSocket == INVALID_SOCKET) {
        cerr << "Fail Create a Socket Object: " << WSAGetLastError() << '\n';
        exit(1);
      }
      // Hostname -> IP
      struct in_addr addr;
      struct hostent* remotehost;
      remotehost = gethostbyname(host.c_str());
      if (remotehost == NULL)
      {
        throw Error("gethostbyname", WSAGetLastError());
      }
      addr.s_addr = *(u_long*)remotehost->h_addr_list[0];
      char ip[16];
      strcpy(ip, inet_ntoa(addr));
      //
      bool hasTimeout = timeout_ms != 0;
      // blocking on
      u_long iMode = 1;
      if (hasTimeout) {
        iResult = ioctlsocket(createdSocket, FIONBIO, &iMode);
        if (iResult != NO_ERROR) {
          throw Error("ioctlsocket", WSAGetLastError());
        }
      }
      // connection info
      sockaddr_in connInfo;
      connInfo.sin_family = AF_INET;
      connInfo.sin_addr.s_addr = inet_addr(ip);
      connInfo.sin_port = htons(port);
      // Connect to server
      iResult = connect(createdSocket, (SOCKADDR*)&connInfo, sizeof(connInfo));
      if (!hasTimeout) {
        if (iResult == SOCKET_ERROR) {
          throw Error("connect", WSAGetLastError());
        }
      }
      else {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
          throw Error("connect", WSAGetLastError());
        }
        TIMEVAL timeout = { 0, timeout_ms };
        fd_set readable, writable;
        FD_ZERO(&readable);
        FD_SET(createdSocket, &readable);
        FD_ZERO(&writable);
        FD_SET(createdSocket, &writable);
        iResult = select(0, &readable, &writable, NULL, &timeout);
        iMode = 0;
        ioctlsocket(createdSocket, FIONBIO, &iMode);
        timeout_ms = 0;
        if (iResult <= 0) {
          throw Error("connect", ETIMEDOUT);
        }
      }
      return *this;
    }
    string read(int length = 0) {
      string res;
      int bytesReceived;
      const int bufferLength = length != 0 && length < MAX_HTTP_BYTES
        ? length
        : MAX_HTTP_BYTES;
      char buffer[bufferLength + 1] = "";
      if (length == 0)
      {
        cout << (length < MAX_HTTP_BYTES);
        while (bytesReceived = recv(createdSocket, buffer, MAX_HTTP_BYTES, 0))
        {
          res.append(buffer);
          memset(buffer, '\0', bytesReceived);
        }
      }
      else
      {
        while (length > 0)
        {
          bytesReceived = recv(createdSocket, buffer, bufferLength, 0);
          length -= bytesReceived;
          res.append(buffer);
          memset(buffer, '\0', bytesReceived);
        }
      }
      return res;
    }
    char readByte() {
      char byte;
      int iResult = recv(createdSocket, &byte, 1, 0);
      return byte;
    }
    void write(string data) {
      int iResult = send(createdSocket, data.c_str(), data.length(), 0);
      if (iResult == SOCKET_ERROR)
      {
        throw Error("send", WSAGetLastError());
      }
    }
    void close() {
      closesocket(createdSocket);
    }
    ~Socket() {
      close();
    }
  };
}