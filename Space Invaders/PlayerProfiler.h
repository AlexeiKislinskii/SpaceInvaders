#pragma once
class CPlayerProfiler
{
public:
  CPlayerProfiler();

  void Reset();
  void ReduceLife();
  void AddScore(size_t score);

  bool IsLifeEnded() const;
  size_t GetScore() const;
  int GetLifesCount() const;

private:
  const int m_MaxLifeCount;
  int       m_LifesCount;
  size_t    m_Score;
};

