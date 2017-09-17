#pragma once
#include "BaseWeapon.h"
#include "../Objects/Bullets/Laser.h"

class CLaserLauncher :
  public IBaseWeapon
{
public:
  CLaserLauncher(EMoveDirection Direction);

private:
  void Fire(CVector2i Position) override;

  EMoveDirection m_Direction;
};

