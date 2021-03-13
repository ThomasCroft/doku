#pragma once
#include <string>

class DancingLinks
{
  class ColumnHeader;
  class DancingNode
  {
  public:
    DancingNode();

    void detachUpDown();
    void detachLeftRight();

    void reattachUpDown();
    void reattachLeftRight();

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

  private:
    size_t m_size;
    std::string m_identifier;

  };
};

