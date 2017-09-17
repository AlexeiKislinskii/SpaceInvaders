#include "PlayerProfiler.h"

CPlayerProfiler::CPlayerProfiler():
  m_LifesCount(3),//take from config or save
  m_Score(0),
  m_GameOver(false)
{
}

void CPlayerProfiler::ReduceLife()
{
  if (m_LifesCount == 0)
  {
    m_GameOver = true;
    return;
  }

  m_LifesCount--;
}

void CPlayerProfiler::AddScore(size_t score)
{
  m_Score += score;
}

bool CPlayerProfiler::IsLifeEnded() const
{
  return m_GameOver;
}

size_t CPlayerProfiler::GetScore() const
{
  return m_Score;
}

size_t CPlayerProfiler::GetLifesCount() const
{
  return m_LifesCount;
}
