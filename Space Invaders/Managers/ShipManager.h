#pragma once
#include "../Objects/Ships/PlayerShip.h"

class CShipManager
{
public:
  CShipManager();

  void Init();

  CPlayerShip & GetPlayerShip() const;

  void StopAllShips() const;

  void OnShipDestruction(IBaseShip * Ship);

private:
  void TrySpawnPlayerShip();
  void TrySpawnEnemyShip();

  CPlayerShip * m_PlayerShip;

  std::vector<IBaseShip *> m_AllShips;
};

