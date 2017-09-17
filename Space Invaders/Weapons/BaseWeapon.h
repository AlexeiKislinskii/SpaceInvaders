#pragma once
#include "../Structs/Vector.h"

class IBaseWeapon
{
public:
  IBaseWeapon(double FireIntervale);
  virtual ~IBaseWeapon() {};

  void TryFire(double Time, CVector2i Position);

private:
  virtual void Fire(CVector2i Position) = 0;

  double m_LastFireTime;
  double m_FireInterval;
};

