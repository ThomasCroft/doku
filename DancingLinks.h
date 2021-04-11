#pragma once
#include <string>
#include <vector>
#include <memory>

#include <SolutionInterface.h>

class DancingLinks
{
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

public:
  DancingLinks();
  void solve() const;

private:
  using Grid = std::vector<std::vector<bool>>;
  void makeBoard(const Grid& grid);
  void validateGrid(const Grid& grid) const;

  ColumnHeader m_headerNode;
  std::vector<std::unique_ptr<ColumnHeader>> m_columns;
  std::vector<std::unique_ptr<DancingNode>> m_nodes;
  Solution_I m_solution;
};

