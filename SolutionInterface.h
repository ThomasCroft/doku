#pragma once
#include <vector>
#include "DancingNode.h"

class SolutionInterface
{
public:
  virtual void handle(std::vector<DancingNode>) = 0;
};

class SudokuSolution : public SolutionInterface
{
public:
  void handle(std::vector<DancingNode>) override;
};