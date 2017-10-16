#include "ShipManager.h"
#include "../Objects/Ships/PlayerShip.h"
#include "../Objects/Ships/EnemyShip.h"
#include "../Game.h"
#include "../Objects/Bullets/Laser.h"

CShipManager::CShipManager() :
  m_PlayerShip(nullptr),
  m_AllShips()
{
}

void CShipManager::Init()
{
  TrySpawnPlayerShip();
  TrySpawnEnemyShip();
  TrySpawnEnemyShip();
}

CPlayerShip & CShipManager::GetPlayerShip() const
{
  return *m_PlayerShip;
}

void CShipManager::StopAllShips() const
{
  for (auto ship : m_AllShips)
    ship->DisableCruiseControl();
}

void CShipManager::OnShipKilling(const IBaseShip * Ship, const IBaseObject * killer)
{
  if (Ship == m_PlayerShip)
    PlayerProfile.ReduceLife();
  else
  {
    if (killer == m_PlayerShip)
      PlayerProfile.AddScore(15);//killed by ram, "Yippee-kai-yay, motherfucker!"
    else
    {
      auto Laser = dynamic_cast<const CLaser *>(killer);//here should be base weapon, not laser
      if (Laser && Laser->GetOwner() == m_PlayerShip)
        PlayerProfile.AddScore(15);//we should take value from player profile
    }
  }
}

  void CShipManager::OnShipDestruction(const IBaseShip * Ship)
{
  if (Ship == m_PlayerShip)
    TrySpawnPlayerShip();
  else
    TrySpawnEnemyShip();

  auto it = std::find(m_AllShips.begin(), m_AllShips.end(), Ship);
  if (it != m_AllShips.end())
    m_AllShips.erase(it);
}

void CShipManager::TrySpawnPlayerShip()
{
  if (PlayerProfile.IsLifeEnded())
    return;

  m_PlayerShip = new CPlayerShip();

  m_AllShips.push_back(m_PlayerShip);

  MapManager.GetCurrentMap().AddObject(m_PlayerShip);
}

void CShipManager::TrySpawnEnemyShip()//try? we do!
{
  IBaseShip * Ship = new CEnemyShip();

  m_AllShips.push_back(Ship);

  MapManager.GetCurrentMap().AddObject(Ship);
}
