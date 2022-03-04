#include "index.hpp"
using namespace std::chrono;
class Timer
{
  steady_clock::time_point oTime = steady_clock::now();
  steady_clock::time_point fTime;
  duration<float> elapsedTime;

public:
  // Methods
  float elapsed()
  {
    fTime = steady_clock::now();
    elapsedTime = fTime - oTime;
    return elapsedTime.count();
  }
  void reset()
  {
    oTime = steady_clock::now();
  }
};