#pragma once
#include <chrono>

class Stopwatch
{
public:
  Stopwatch();
  void reset();
  double millisecondsElapsed() const;

private:
  std::chrono::steady_clock::time_point m_start;
};

