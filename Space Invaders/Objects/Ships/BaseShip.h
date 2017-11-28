#pragma once
#include "../BaseObject.h"
#include "../../Weapons/BaseWeapon.h"
#include "../../Enums/MoveDirection.h"

class IBaseShip :
  public IBaseObject
{
public:
  IBaseShip(EMoveDirection direction);
  ~IBaseShip();

  void DisableCruiseControl();

protected:
  void Update(double time);

  bool TryMove(const CVector2i & moveVector, bool force = false);

  IBaseWeapon * m_Weapon;

private:
  bool m_IsCruiseControleEnebled;

  CVector2i m_CruiseControleVector;
};

