#include "ShipManager.h"
#include "../Objects/Ships/PlayerShip.h"
#include "../Objects/Ships/EnemyShip.h"
#include "../Game.h"

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

void CShipManager::OnShipDestruction(IBaseShip * Ship)
{
  if (Ship == m_PlayerShip)
  {
    PlayerProfile.ReduceLife();
    TrySpawnPlayerShip();
  }
  else
  {
    //enemy crashed in rock and player get points for that?
    PlayerProfile.AddScore(15);//hack! here should be get price from ship!
    TrySpawnEnemyShip();
  }

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
