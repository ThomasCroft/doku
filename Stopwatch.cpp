#include "Stopwatch.h"

Stopwatch::Stopwatch() :
  m_start(std::chrono::steady_clock::now())
{
}

void Stopwatch::reset()
{
  m_start = std::chrono::steady_clock::now();
}

double Stopwatch::millisecondsElapsed() const
{
  const auto diff = std::chrono::steady_clock::now() - m_start;
  return std::chrono::duration <double, std::milli>(diff).count();
}
