#include "BaseWeapon.h"

IBaseWeapon::IBaseWeapon(CVector2i bulletOffset, EMoveDirection direction, double fireIntervale) :
  m_BulletOffset(bulletOffset),
  m_Direction(direction),
  m_LastFireTime(0)
{
  m_FireInterval = fireIntervale;
}

IBaseWeapon::~IBaseWeapon()
{
  // Empty 
}

void IBaseWeapon::TryFire(double Time)
{
  if (Time - m_LastFireTime < m_FireInterval)
    return;

  m_LastFireTime = Time;

  Fire();
}