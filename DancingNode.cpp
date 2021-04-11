#include "DancingNode.h"

DancingNode::DancingNode(ColumnHeader* header) :
  m_up(this),
  m_down(this),
  m_left(this),
  m_right(this),
  m_column(header)
{
}

void DancingNode::detachUpDown()
{
  m_up->m_down = m_down;
  m_down->m_up = m_up;
}

void DancingNode::detachLeftRight()
{
  m_left->m_right = m_right;
  m_right->m_left = m_left;
}

void DancingNode::reattachUpDown()
{
  m_up->m_down = this;
  m_down->m_up = this;
}

void DancingNode::reattachLeftRight()
{
  m_left->m_right = this;
  m_right->m_left = this;
}

void DancingNode::addNodeRight(DancingNode* nodeToAdd)
{
  nodeToAdd->m_right = m_right;
  nodeToAdd->m_right->m_left = nodeToAdd;
  nodeToAdd->m_left = this;
  m_right = nodeToAdd;
}

void DancingNode::addNodeBelow(DancingNode* nodeToAdd)
{
  nodeToAdd->m_down = m_down;
  nodeToAdd->m_down->m_up;
  nodeToAdd->m_up = this;
  m_down = nodeToAdd;
}

ColumnHeader::ColumnHeader(const std::string& identifier) :
  DancingNode(this),
  m_size(),
  m_identifier(identifier)
{
}

void ColumnHeader::cover()
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

void ColumnHeader::uncover()
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
