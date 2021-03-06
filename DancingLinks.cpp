#include "DancingLinks.h"

DancingLinks::DancingLinks(SolutionInterface *solution) :
  m_headerNode("header"),
  m_columns(),
  m_nodes(),
  m_result(),
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

ColumnHeader* DancingLinks::getSmallestColumn() const
{
  ColumnHeader* result = nullptr;
  unsigned int smallest = UINT_MAX;
  for (auto& column : m_columns)
  {
    if ((*column).m_size < smallest)
    {
      smallest = (*column).m_size;
      result = column.get();
    }
  }
  return result;
}

// TODO: Break this down into smaller functions
void DancingLinks::solve()
{
  // We have reached the solution. Pass it to the solution handler to interpret it.
  if (m_headerNode.m_right == &m_headerNode)
  {
    m_solution->handle(m_result);
    return;
  }

  auto* columnNode = getSmallestColumn();
  columnNode->cover();

  // Add all the nodes in the column to the answer
  for (auto* nodeInColumn = columnNode->m_down; nodeInColumn != columnNode; nodeInColumn = nodeInColumn->m_down)
  {
    m_result.push_back(*nodeInColumn);

    // Cover all the columns horizontally linked to this node
    for (auto* nodeInColumnToCover = nodeInColumn->m_right; nodeInColumnToCover != nodeInColumn; nodeInColumnToCover->m_right)
    {
      nodeInColumnToCover->m_column->cover();
    }

    solve();

    // If we are here, the solution is not correct. Uncover nodes.

    // remove the node from the result
    m_result.pop_back();

    // TODO: do we need this?
    columnNode = nodeInColumn->m_column;

    for (auto *nodeInColumnToUncover = nodeInColumn->m_left; nodeInColumnToUncover != nodeInColumn; nodeInColumnToUncover->m_left)
    {
      nodeInColumnToUncover->m_column->uncover();
    }
  }

  columnNode->uncover();
}