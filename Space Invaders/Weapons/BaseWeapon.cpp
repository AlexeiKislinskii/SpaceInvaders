#include "BaseWeapon.h"

IBaseWeapon::IBaseWeapon(double FireIntervale) :
  m_LastFireTime(0)
{
  m_FireInterval = FireIntervale;
}

void IBaseWeapon::TryFire(double Time, CVector2i Position)
{
  if (Time - m_LastFireTime < m_FireInterval)
    return;

  m_LastFireTime = Time;

  Fire(Position);
}