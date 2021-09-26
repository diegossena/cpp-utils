#include "index.hpp"
namespace Printer {
  // Query(string host)
  class Query {
    Snmp snmp;
    bool percentualValue = false;
    // OIDs
    string
      serial = "1.3.6.1.2.1.43.5.1.1.17.1", model = "1.3.6.1.2.1.25.3.2.1.3.1", status = "1.3.6.1.2.1.43.16.5.1.2.1.1",
      // Counter
      pb, color, scanner,
      // Toners
      tonerC, tonerM, tonerY, tonerK,
      // Drums
      drumC, remainingDrumC, usedDrumC,
      drumM, remainingDrumM, usedDrumM,
      drumY, remainingDrumY, usedDrumY,
      drumK, remainingDrumK, usedDrumK,
      // Parts
      fuser, remainingFuser, usedFuser,
      belt, remainingBelt, usedBelt;
    // Utils
    int getAsNumber(string& oid) {
      return atoi(snmp.get(oid).c_str());
    }
  public:
    // Getters
    string getSerial() { return snmp.get(serial); }
    string getModel() { return snmp.get(model); }
    string getStatus() { return snmp.get(status); }
    int getPb() { return getAsNumber(pb); }
    int getColor() { return getAsNumber(color); }
    int getScanner() { return getAsNumber(scanner); }
    // Constructor
    Query(string host) : snmp(host) {
      string sysOid = String::split("1.3.6.1.4.1.2001", ".").back();//snmp.get("sysObjectID.0");
      if (sysOid.substr(0, 7) == "Timeout") {
        throw Error("Printer", ETIMEDOUT);
      }
      int sysId = atoi(sysOid.c_str());
      switch (sysId) {
      case 2001: {
        serial = "1.3.6.1.4.1.2001.1.1.1.1.11.1.10.45.0";
        pb = "1.3.6.1.4.1.2001.1.1.1.1.11.1.10.170.1.7.1";
        scanner = "1.3.6.1.4.1.2001.1.1.4.2.1.3.10.0";
        model = "1.3.6.1.4.1.2001.1.1.1.1.11.1.10.540.0";
        fuser = "1.3.6.1.4.1.2001.1.1.1.1.100.6.1.1.4";
        usedFuser = "1.3.6.1.4.1.2001.1.1.1.1.100.6.1.1.3.1";
        percentualValue = true;
        tonerK = "1.3.6.1.4.1.2001.1.1.1.1.100.3.1.1.3.1";
        drumK = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.4.1";
        usedDrumK = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.3.1";
        status = "1.3.6.1.4.1.2001.1.3.1.1.7.1.2.1.1";
        if (snmp.get("1.3.6.1.4.1.2001.1.1.1.1.11.1.10.70.0") == "MONO") {
          color = "1.3.6.1.4.1.2001.1.1.1.1.11.1.10.170.1.6.1";
          belt = "1.3.6.1.4.1.2001.1.1.1.1.100.5.1.1.4";
          usedBelt = "1.3.6.1.4.1.2001.1.1.1.1.100.5.1.1.3";
          tonerC = "1.3.6.1.4.1.2001.1.1.1.1.100.3.1.1.3.2";
          tonerM = "1.3.6.1.4.1.2001.1.1.1.1.100.3.1.1.3.3";
          tonerY = "1.3.6.1.4.1.2001.1.1.1.1.100.3.1.1.3.4";
          drumC = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.4.2";
          drumM = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.4.3";
          drumY = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.4.4";
          usedDrumC = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.3.2";
          usedDrumM = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.3.3";
          usedDrumY = "1.3.6.1.4.1.2001.1.1.1.1.100.4.1.1.3.4";
        }
        break;
      }
      }
    }
  };
}