#pragma once
#include <vector>
#include <iostream>

class Base
{
public:
  using Set = std::vector<unsigned int>;

  Base();
  Base(std::istream& is);
  ~Base() = default;

  friend std::ostream& operator<<(std::ostream& os, const Base& base);
  friend std::istream& operator>>(std::istream& is, Base& base);

  bool verify();
  bool complete();

  void solveByBacktrack();

private:
  Set getRow(unsigned int rowIdx);
  Set getColumn(unsigned int columnIdx);
  Set getBox(unsigned int rowIdx, unsigned int columnIdx);

  bool validateCell(unsigned int rowIdx, unsigned int columnIdx);
  bool isUnique(unsigned int idx, const Set &set) const;
  unsigned int getPositionInBox(unsigned int rowIdx, unsigned int columnIdx) const;

  void backtrack(unsigned int &rowIdx, unsigned int &columnIdx);

  using Board = std::vector<Set>;
  Board m_board;

  std::vector<std::vector<bool>> m_clueTable;
};

std::ostream& operator<<(std::ostream& os, const Base& base);
std::istream& operator>>(std::istream& is, Base& base);
