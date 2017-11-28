#pragma once
#include "../Objects/Ships/PlayerShip.h"

class CShipManager :
  public IUpdateable
{
public:
  CShipManager();

  void Init();

  const CPlayerShip * GetPlayerShip() const;

  void StopAllShips() const;

protected:
  void Update( double time ) override;

private:
  void TrySpawnPlayerShip();
  void TrySpawnEnemyShip();

  CPlayerShip * m_PlayerShip;
};

