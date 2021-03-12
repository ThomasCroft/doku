#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Stopwatch.h"
#include "Base.h"

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Invalid number of arguments" << std::endl;
    return 1;
  }

  const std::string inputFilename = argv[1];
  std::cout << "Input filename: " << inputFilename << std::endl;

  std::ifstream ifs;
  // ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  ifs.ignore(9);

  try
  {
    ifs.open(inputFilename);
  }
  catch(const std::ifstream::failure &e)
  {
    std::cout << "Caught exception: " << e.what() << std::endl;
    return 1;
  }

  Base sudo{ifs};
  Stopwatch stopwatch{};
  std::cout << "Solve by backtrack" << std::endl;
  sudo.solveByBacktrack();
  std::cout << stopwatch.millisecondsElapsed() << " ms" << std::endl;
  std::cout << sudo << std::endl;
  int a;
  std::cin >> a;
  return 0;
}
