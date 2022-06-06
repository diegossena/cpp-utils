#pragma once
#include <winsock2.h>
#include <iostream>
#include <algorithm>
#include "Error.hpp"
using namespace std;
#define MAX_HTTP_BYTES 1001654
class WinSock2
{
public:
  WinSock2() {
    // Inicialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
      Error("WSAStartup", iResult);
  }
  ~WinSock2() {
    WSACleanup();
  }
} WinSock2;
class Socket {
  SOCKET connectSocket = INVALID_SOCKET;
  long int timeout_ms = 0;
public:
  Socket(string host, u_short port) {
    int iResult;
    // Hostname -> IP
    struct in_addr addr;
    struct hostent* remotehost;
    remotehost = gethostbyname(host.c_str());
    if (remotehost == NULL)
      Error("gethostbyname", WSAGetLastError());
    addr.s_addr = *(u_long*)remotehost->h_addr_list[0];
    char ip[16];
    strcpy(ip, inet_ntoa(addr));
    // Create a Socket Object
    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET)
      Error("socket", WSAGetLastError());
    //
    bool hasTimeout = timeout_ms != 0;
    // blocking on
    u_long iMode = 1;
    if (hasTimeout) {
      iResult = ioctlsocket(connectSocket, FIONBIO, &iMode);
      if (iResult != NO_ERROR)
        Error("ioctlsocket", WSAGetLastError());
    }
    // connection info
    sockaddr_in connInfo;
    connInfo.sin_family = AF_INET;
    connInfo.sin_addr.s_addr = inet_addr(ip);
    connInfo.sin_port = htons(port);
    // Connect to server
    iResult = connect(connectSocket, (SOCKADDR*)&connInfo, sizeof(connInfo));
    if (!hasTimeout) {
      if (iResult == SOCKET_ERROR)
        Error("connect", WSAGetLastError());
    }
    else {
      if (WSAGetLastError() != WSAEWOULDBLOCK)
        Error("connect", WSAGetLastError());
      TIMEVAL timeout = { 0, timeout_ms };
      fd_set readable, writable;
      FD_ZERO(&readable);
      FD_SET(connectSocket, &readable);
      FD_ZERO(&writable);
      FD_SET(connectSocket, &writable);
      iResult = select(0, &readable, &writable, NULL, &timeout);
      iMode = 0;
      ioctlsocket(connectSocket, FIONBIO, &iMode);
      timeout_ms = 0;
      if (iResult <= 0)
        Error("connect", ETIMEDOUT);
    }
  }
  Socket& setTimeout(unsigned miliseconds) {
    timeout_ms = miliseconds * 1000;
    return *this;
  }
  string read(int length = 0) {
    string res;
    int bytesReceived = 0;
    const int bufferLength = min(length, MAX_HTTP_BYTES);
    char buffer[bufferLength + 1] = "";
    if (length == 0)
    {
      cout << (length < MAX_HTTP_BYTES);
      while (bytesReceived = recv(connectSocket, buffer, MAX_HTTP_BYTES, 0))
      {
        res.append(buffer);
        memset(buffer, '\0', bytesReceived);
      }
    }
    else
    {
      while (length > 0)
      {
        bytesReceived = recv(connectSocket, buffer, bufferLength, 0);
        length -= bytesReceived;
        res.append(buffer);
        memset(buffer, '\0', bytesReceived);
      }
    }
    return res;
  }
  char readByte() {
    char byte;
    int iResult = recv(connectSocket, &byte, 1, 0);
    return byte;
  }
  void write(string data) {
    int iResult = send(connectSocket, data.c_str(), data.length(), 0);
    if (iResult == SOCKET_ERROR)
      Error("send", WSAGetLastError());
  }
  ~Socket() {
    closesocket(connectSocket);
  }
};