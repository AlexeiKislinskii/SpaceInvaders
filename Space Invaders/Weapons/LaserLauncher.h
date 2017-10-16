#pragma once
#include "BaseWeapon.h"
#include "../Objects/Ships/BaseShip.h"

class CLaserLauncher :
  public IBaseWeapon
{
public:
  CLaserLauncher(IBaseShip * owner, CVector2i bulletOffset, EMoveDirection fireDirection);

protected:
  void Fire() override;

private:
  IBaseShip * m_Owner;
};

