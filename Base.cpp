#include "Base.h"

Base::Base() : m_board(),
               m_clueTable()
{}

Base::Base(std::istream& is) : m_board(),
                               m_clueTable()
{
  is >> *this;
}

std::ostream& operator<<(std::ostream& os, const Base& base)
{
  os << "base:" << std::endl;

  for(auto &vec : base.m_board)
  {
    for(auto &i : vec)
    {
      os << i << ", ";
    }
    os << std::endl;
  }

  return os;
}

std::istream& operator>>(std::istream& is, Base& base)
{
  while(is.eof() == false)
  {
    std::string line;
    Base::Set row;
    std::vector<bool> clueRow;

    std::getline(is, line);
    if(line.empty() == true)
      continue;

    for(auto& c : line)
    {
      int value = static_cast<int> (c - '0');

      if(value == 0)
        clueRow.push_back(false);
      else
        clueRow.push_back(true);

      row.push_back(value);
    }
    base.m_board.push_back(row);
    base.m_clueTable.push_back(clueRow);
  }

  return is;
}

bool Base::verify()
{
  return false;
}

bool Base::complete()
{
  return false;
}

void Base::backtrack(unsigned int &rowIdx, unsigned int &columnIdx)
{
  do
  {
    if(columnIdx == 0)
    {
      if(rowIdx == 0)
      {
        std::cout << "Uh-oh!" << std::endl;
        return;
      }

      --rowIdx;
      columnIdx = m_board[rowIdx].size() - 1;
    }
    else
    {
      --columnIdx;
    }
  } while(m_clueTable[rowIdx][columnIdx] == true);
}

void Base::solveByBackTrack()
{
  for(unsigned int rowIdx = 0; rowIdx < m_board.size(); ++rowIdx)
  {
    for(unsigned int columnIdx = 0; columnIdx < m_board[rowIdx].size();)
    {
      if(m_clueTable[rowIdx][columnIdx] == true)
      {
        ++columnIdx;
      }
      else if(m_board[rowIdx][columnIdx] == 0)
      {
        ++m_board[rowIdx][columnIdx];
      }
      else if(validateCell(rowIdx, columnIdx) == true)
      {
        ++columnIdx;
      }
      else if(m_board[rowIdx][columnIdx] == 9)
      {
        do
        {
          m_board[rowIdx][columnIdx] = 0;
          backtrack(rowIdx, columnIdx);
        } while(m_board[rowIdx][columnIdx] == 9);

        ++m_board[rowIdx][columnIdx];
      }
      else
      {
        ++m_board[rowIdx][columnIdx];
      }
    }
  }
}

Base::Set Base::getRow(unsigned int rowIdx)
{
  return m_board[rowIdx];
}

Base::Set Base::getColumn(unsigned int columnIdx)
{
  Base::Set column;

  for(const auto& row : m_board)
  {
    column.push_back(row[columnIdx]);
  }

  return column;
}

Base::Set Base::getBox(unsigned int rowIdx, unsigned int columnIdx)
{
  unsigned int boxRowIdxStart = rowIdx - (rowIdx % 3);
  unsigned int boxColumnIdxStart = columnIdx - (columnIdx % 3);

  Base::Set box{};

  for(unsigned int i = boxRowIdxStart; i < boxRowIdxStart + 3; ++i)
  {
    for(unsigned int j = boxColumnIdxStart; j < boxColumnIdxStart + 3; ++j)
    {
      box.push_back(m_board[i][j]);
    }
  }
  return box;
}

bool Base::validateCell(unsigned int rowIdx, unsigned int columnIdx)
{
  if(isUnique(columnIdx, m_board[rowIdx]) == false)
    return false;

  Set column = getColumn(columnIdx);
  if(isUnique(rowIdx, column) == false)
    return false;

  Set box = getBox(rowIdx, columnIdx);
  if(isUnique(getPositionInBox(rowIdx, columnIdx), box) == false)
    return false;

  return true;
}

bool Base::isUnique(unsigned int idx, const Set &set) const
{
  unsigned int numberToTest = set[idx];
  for(unsigned int i = 0; i < set.size(); ++i)
  {
    if(i == idx)
      continue;

    if (set[i] == numberToTest)
    {
      return false;
    }
  }
  return true;
}

unsigned int Base::getPositionInBox(unsigned int rowIdx, unsigned int columnIdx) const
{
  return ((3 * (rowIdx % 3)) + (columnIdx % 3));
}


