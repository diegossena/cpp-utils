#include "index.hpp"
bool ipEqual(unsigned char* ip1, unsigned char* ip2) {
  for (int i = 0; i < 4; i++) {
    if (ip1[i] != ip2[i])
      return false;
  }
  return true;
}
void ipParse(unsigned char* dest, char* ip_str) {
  char* ptr;
  ptr = strtok(ip_str, ".");
  int i = 0;
  while (true) {
    dest[i] = atoi(ptr);
    if (i == 3)
      return;
    ptr = strtok(NULL, ".");
    i++;
  };
}
void printerCollect(string host, int timeout_ms, bool showPing = false) {
  cout << host << " - Checking...";
  try {
    net::Socket()
      .setTimeout(timeout_ms)
      .createConnection(host, 80)
      .close();
  }
  catch (Error error) {
    if (error.errnum == ETIMEDOUT) {
      if (!showPing) {
        Console::backspace(host.length() + 14);
      }
    }
    else {
      error.what();
      cout << '\n';
    }
    return;
  }
  Console::backspace(11);
  cout << "Querying...";
  try {
    Printer::Query printer(host);
    cout << printer.getPb() << '\n';
  }
  catch (Error error) {
    cout << "error";
  }
  //cout << "sysOid: " << String::split(sysOid, ".")[0] << "\n";
}
int main(int argc, char** argv) {
  switch (argc) {
  case 3: {
    string host = argv[1];
    int ms = atoi(argv[2]);
    printerCollect(host, ms, true);
    break;
  }
  case 4: {
    int ms = atoi(argv[3]);
    unsigned char ipRange[2][4];
    ipParse(ipRange[0], argv[1]);
    ipParse(ipRange[1], argv[2]);
    char currentIp[16];
    while (true) {
      sprintf(currentIp, "%u.%u.%u.%u", ipRange[0][0], ipRange[0][1], ipRange[0][2], ipRange[0][3]);
      printerCollect(currentIp, ms);
      if (ipEqual(ipRange[0], ipRange[1]))
        break;
      // Calc Next
      for (int i = 3; i >= 0; i--) {
        if (ipRange[0][i] == 255) {
          ipRange[0][i] = 0;
          if (i != 0) {
            ipRange[0][i - 1]++;
          }
        }
      }
      ipRange[0][3]++;
    };
    break;
  }
  default:
    cout
      << " ==========================================================================\n"
      << "|\t\t\t\tComandos:\t\t\t\t   |\n"
      << "|==========================================================================|\n"
      << "| <jrb-monitor> <host> <ms> : Coleta uma maquina especifica\t\t   |\n"
      << "| <jrb-monitor> <ip inicial> <ip final> <ms> : Coleta a faixa especificada |\n"
      << " ==========================================================================\n";
    system("PAUSE");
  }
  return 0;
}