#include "Updateable.h"

IUpdateable::IUpdateable(EUpdateSpeed updateSpeed) :
  m_LastUpdateTime(0)
{
  m_UpdateInterval = GetUpdateIntervale(updateSpeed);
}

void IUpdateable::TryUpdate(double time)
{
  if (time - m_LastUpdateTime < m_UpdateInterval)
    return;

  Update(time);

  m_LastUpdateTime = time;
}
