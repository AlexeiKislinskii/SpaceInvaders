#include "Updateable.h"

IUpdateable::IUpdateable(EUpdateSpeed updateSpeed) :
  m_NextUpdateTime(0),
  m_PauseTime(0),
  m_IsPaused(true) //is it logicaly correct?
{
  m_UpdateInterval = GetUpdateIntervale(updateSpeed);
}

void IUpdateable::TryUpdate(double time)
{
  if (m_IsPaused)
  {
    m_NextUpdateTime += time - m_PauseTime;
    m_IsPaused = false;
  }

  if (time < m_NextUpdateTime)
    return;

  Update(time);

  m_NextUpdateTime = time + m_UpdateInterval;
}

void IUpdateable::PauseUpdate(double time)
{
  if (m_IsPaused)
    return;

  m_PauseTime = time;
  m_IsPaused = true;
}