#include "DancingLinks.h"

DancingLinks::DancingNode::DancingNode(ColumnHeader* header) :
  m_up(this),
  m_down(this),
  m_left(this),
  m_right(this),
  m_column(header)
{
}

void DancingLinks::DancingNode::detachUpDown()
{
  m_up->m_down = m_down;
  m_down->m_up = m_up;
}

void DancingLinks::DancingNode::detachLeftRight()
{
  m_left->m_right = m_right;
  m_right->m_left = m_left;
}

void DancingLinks::DancingNode::reattachUpDown()
{
  m_up->m_down = this;
  m_down->m_up = this;
}

void DancingLinks::DancingNode::reattachLeftRight()
{
  m_left->m_right = this;
  m_right->m_left = this;
}

void DancingLinks::DancingNode::addNodeRight(DancingLinks::DancingNode* nodeToAdd)
{
  nodeToAdd->m_right = m_right;
  nodeToAdd->m_right->m_left = nodeToAdd;
  nodeToAdd->m_left = this;
  m_right = nodeToAdd;
}

void DancingLinks::DancingNode::addNodeBelow(DancingLinks::DancingNode* nodeToAdd)
{
  nodeToAdd->m_down = m_down;
  nodeToAdd->m_down->m_up;
  nodeToAdd->m_up = this;
  m_down = nodeToAdd;
}

DancingLinks::ColumnHeader::ColumnHeader(const std::string& identifier) :
  DancingNode(this),
  m_size(),
  m_identifier(identifier)
{
}

void DancingLinks::ColumnHeader::cover()
{
  for (auto* columnLink = m_down; columnLink != this; columnLink = columnLink->m_down)
  {
    for (auto* rowLink = columnLink->m_right; rowLink != columnLink; rowLink = rowLink->m_right)
    {
      rowLink->detachUpDown();
      --(rowLink->m_column->m_size);
    }
  }
}

void DancingLinks::ColumnHeader::uncover()
{
  for (auto* columnLink = m_up; columnLink != this; columnLink = columnLink->m_up)
  {
    for (auto* rowLink = columnLink->m_left; rowLink != columnLink; rowLink = rowLink->m_left)
    {
      rowLink->reattachUpDown();
      ++(rowLink->m_column->m_size);
    }
  }
}

DancingLinks::DancingLinks() :
  m_headerNode("header"),
  m_columns(),
  m_nodes()
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
    m_solution.handle(result);
  }
}