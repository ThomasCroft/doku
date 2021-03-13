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

}