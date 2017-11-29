#include "PlayerProfiler.h"

CPlayerProfiler::CPlayerProfiler():
  m_MaxLifeCount(3),
  m_LifesCount(0),//take from config or save
  m_Score(0)
{
  Reset();
}

void CPlayerProfiler::Reset()
{
  m_LifesCount = m_MaxLifeCount;
  m_Score = 0;
}

void CPlayerProfiler::ReduceLife()
{
  m_LifesCount--;
}

void CPlayerProfiler::AddScore(size_t score)
{
  m_Score += score;
}

bool CPlayerProfiler::IsLifeEnded() const
{
  return m_LifesCount < 0;
}

size_t CPlayerProfiler::GetScore() const
{
  return m_Score;
}

int CPlayerProfiler::GetLifesCount() const
{
  return m_LifesCount;
}
