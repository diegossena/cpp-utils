#include <chrono>
using namespace std::chrono;
class Date
{
public:
  Date() {}
  uint64_t getTime() {
    return duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
      ).count();
  }
};