#pragma once
#include <string>
#include <vector>
#include <memory>

#include "DancingNode.h"
#include "SolutionInterface.h"

class DancingLinks
{
public:
  DancingLinks(SolutionInterface* solution);
  void solve() const;

private:
  using Grid = std::vector<std::vector<bool>>;
  void makeBoard(const Grid& grid);
  void validateGrid(const Grid& grid) const;

  ColumnHeader m_headerNode;
  std::vector<std::unique_ptr<ColumnHeader>> m_columns;
  std::vector<std::unique_ptr<DancingNode>> m_nodes;
  SolutionInterface* m_solution;
};

