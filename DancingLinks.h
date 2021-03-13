#pragma once
class DancingLinks
{
  class DancingNode final
  {
  public:
    void detachUpDown();
    void detachLeftRight();

    void reattachUpDown();
    void reattachLeftRight();

  private:
    DancingNode* m_up;
    DancingNode* m_down;
    DancingNode* m_left;
    DancingNode* m_right;
  };
};

