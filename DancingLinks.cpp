#include "DancingLinks.h"

DancingLinks::DancingNode::DancingNode() :
  m_up(this),
  m_down(this),
  m_left(this),
  m_right(this),
  m_column()
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
  DancingNode(),
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

void DancingLinks::makeBoard(const std::vector<std::vector<bool>>& grid)
{
  const size_t NUM_COLUMNS = grid.size();
  if (NUM_COLUMNS == 0)
  {
    return;
  }
  const size_t NUM_ROWS = grid[0].size();
  if (NUM_ROWS == 0)
  {
    return;
  }

  ColumnHeader headerNode{"header"};

  auto& previousNode = headerNode;
  for (unsigned int columnIdx = 0; columnIdx < NUM_COLUMNS; ++columnIdx)
  {
    ColumnHeader columnNode{"column " + columnIdx};
    static_cast<DancingNode>(previousNode).addNodeRight(&columnNode);
    previousNode = columnNode;
  }
}