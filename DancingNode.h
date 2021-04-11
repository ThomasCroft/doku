#pragma once
#include <string>

class ColumnHeader;
class DancingNode
{
public:
  DancingNode(ColumnHeader* header);

  void detachUpDown();
  void detachLeftRight();

  void reattachUpDown();
  void reattachLeftRight();

  void addNodeRight(DancingNode* nodeToAdd);
  void addNodeBelow(DancingNode* nodeToAdd);

public:
  DancingNode* m_up;
  DancingNode* m_down;
  DancingNode* m_left;
  DancingNode* m_right;
  ColumnHeader* m_column;
};

class ColumnHeader : public DancingNode
{
public:
  ColumnHeader(const std::string& identifier);

  void cover();
  void uncover();

public:
  size_t m_size;

private:
  std::string m_identifier;

};