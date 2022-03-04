#include "index.hpp"
// snmpget -v 2c -c public 10.1.9.100 .1.3.6.1.2.1.2.2.1.5.25 .1.3.6.1.2.1.2.2.1.10.25
#define SNMP_WALK_PATH "bin\\snmpwalk -v 1 -c public -r1 -t1 -O vqn -M mibs "
class Snmp {
  string host;
public:
  Snmp(string host) : host(host) {}
  string get(string oid) {
    string cmd = SNMP_WALK_PATH + host + ' ' + oid + " 2>&1";
    string result = System::exec(cmd);
    return result;
  }
};