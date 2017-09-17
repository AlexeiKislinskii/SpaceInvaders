#pragma once
class CPlayerProfiler
{
public:
  CPlayerProfiler();

  void ReduceLife();
  void AddScore(size_t score);

  bool IsLifeEnded() const;
  size_t GetScore() const;
  size_t GetLifesCount() const;

private:
  size_t m_LifesCount;
  size_t m_Score;
  bool m_GameOver;
};

