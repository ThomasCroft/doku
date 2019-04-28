#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

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
  //ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
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
	auto start = std::chrono::steady_clock::now();
	std::cout << "Solve by backtrack" << std::endl;
	sudo.solveByBackTrack();
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
	std::cout << sudo << std::endl;
	return 0;
}
