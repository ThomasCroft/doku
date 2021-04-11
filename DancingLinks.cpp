#include "DancingLinks.h"

DancingLinks::DancingLinks(SolutionInterface *solution) :
  m_headerNode("header"),
  m_columns(),
  m_nodes(),
  m_solution(solution)
{
}

void DancingLinks::makeBoard(const Grid& grid)
{
  validateGrid(grid);

  const size_t NUM_COLUMNS = grid.size();
  const size_t NUM_ROWS = grid[0].size();
  ColumnHeader headerNode{"header"};

  auto& previousColumnNode = headerNode;
  for (unsigned int columnIdx = 0; columnIdx < NUM_COLUMNS; ++columnIdx)
  {
    // Add the column nodes
    m_columns.emplace_back(std::make_unique<ColumnHeader>("column " + columnIdx));
    auto& columnNode = *(m_columns.back());
    static_cast<DancingNode>(previousColumnNode).addNodeRight(&columnNode);
    previousColumnNode = columnNode;
  }

  for (unsigned int rowIdx = 0; rowIdx < NUM_ROWS; ++rowIdx)
  {
    DancingNode* previousNode_p = nullptr;
    for (unsigned int columnIdx = 0; columnIdx < NUM_COLUMNS; ++columnIdx)
    {
      if (grid[rowIdx][columnIdx] == true)
      {
        // Add the node
        auto *columnHeader_p = m_columns[columnIdx].get();
        m_nodes.emplace_back(std::make_unique<DancingNode>(columnHeader_p));
        auto *newNode_p = m_columns.back().get();

        if (previousNode_p == nullptr)
        {
          previousNode_p = newNode_p;
        }

        columnHeader_p->m_up->addNodeBelow(newNode_p);
        previousNode_p->addNodeRight(newNode_p);
        previousNode_p = newNode_p;
        ++columnHeader_p->m_size;
      }
    }
  }
}

void DancingLinks::validateGrid(const Grid& grid) const
{
  if (grid.size() == 0 ||
      grid[0].size() == 0)
  {
    throw std::exception("Invalid grid size. Grid must contain at least 1 column and 1 row.");
  }

  const auto& columnSize = grid[0].size();

  for (const auto& column : grid)
  {
    if (column.size() != columnSize)
    {
      throw std::exception("Column lengths must all be equal.");
    }

  }
}

void DancingLinks::solve() const
{
  std::vector<DancingNode> result;
  if (m_headerNode.m_right == &m_headerNode)
  {
    m_solution->handle(result);
  }
}