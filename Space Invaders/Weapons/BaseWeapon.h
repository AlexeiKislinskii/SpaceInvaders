#pragma once
#include "../Structs/Vector.h"
#include "../Enums/MoveDirection.h"

class IBaseWeapon
{
public:
  IBaseWeapon(CVector2i bulletOffset, EMoveDirection direction, double fireIntervale);
  virtual ~IBaseWeapon();

  void TryFire(double Time);

protected:
  virtual void Fire() = 0;

  CVector2i m_BulletOffset;
  EMoveDirection m_Direction;

private:
  double m_LastFireTime;
  double m_FireInterval;
};

