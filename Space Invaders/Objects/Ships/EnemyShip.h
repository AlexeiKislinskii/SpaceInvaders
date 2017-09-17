#pragma once
#include "BaseShip.h"

class CEnemyShip :
  public IBaseShip
{
public:
  CEnemyShip();
  ~CEnemyShip();

  void Update(double time) override;

private:
  enum SHIP_STATE
  {
    SPAWNING,
    FLYING,
    FIRING
  };

  void RandomizeMoveVector();

  SHIP_STATE m_State;
  CVector2i m_MoveVector;
  int m_FireIntervaleInUpdates;
};

