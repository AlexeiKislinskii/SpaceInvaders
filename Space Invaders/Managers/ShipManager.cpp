#include "ShipManager.h"
#include "../Objects/Ships/PlayerShip.h"
#include "../Objects/Ships/EnemyShip.h"
#include "../Game.h"
#include "../Objects/Bullets/Laser.h"

CShipManager::CShipManager() :
  IUpdateable(FAST_UPDATE),
  m_PlayerShip(nullptr)
{
}

void CShipManager::Init()
{
  TrySpawnPlayerShip();
  TrySpawnEnemyShip();
  TrySpawnEnemyShip();
}

const CPlayerShip * CShipManager::GetPlayerShip() const
{
  return m_PlayerShip;
}

void CShipManager::StopAllShips() const
{
  auto Objects = MapManager.GetCurrentMap().GetAllObjects();
  for (auto obj : Objects)
  {
    auto ship = dynamic_cast<IBaseShip *>(obj);
    if (!ship)
      continue;
  
    ship->DisableCruiseControl();
  }
}

void CShipManager::Update(double time)
{
  auto Objects = MapManager.GetCurrentMap().GetAllObjects();
  m_PlayerShip = nullptr;
  for (auto obj : Objects)
  {
    if (!dynamic_cast<const IBaseShip *>(obj))
      continue;

    auto playerShip = dynamic_cast<CPlayerShip *>(obj);

    if (playerShip)
      m_PlayerShip = playerShip;
  }

  if (!m_PlayerShip)
    TrySpawnPlayerShip();

  if (!m_PlayerShip)
    return;

  size_t EnemysShipCount = 0;
  for (auto obj : Objects)
  {
    if (!dynamic_cast<const IBaseShip *>(obj))
      continue;

    auto enemyShip = dynamic_cast<CEnemyShip *>(obj);

    if (enemyShip)
      EnemysShipCount++;

    if (obj->IsDead())
    {
      if (enemyShip)
      {
        auto killer = obj->GetKiller();
        if (killer == m_PlayerShip)
          PlayerProfile.AddScore(15);//killed by ram, "Yippee-kai-yay, motherfucker!"
        else if(killer->GetOwner() == m_PlayerShip)
          PlayerProfile.AddScore(15);//killed by bullet, we should take value from player profile
      }
      else
        PlayerProfile.ReduceLife();
    }
  }

  for (auto i = 0; i < 2 - EnemysShipCount; i++)
    TrySpawnEnemyShip();
}

void CShipManager::TrySpawnPlayerShip()
{
  if (PlayerProfile.IsLifeEnded())
    return;

  m_PlayerShip = new CPlayerShip();

  MapManager.GetCurrentMap().AddObject(m_PlayerShip);
}

void CShipManager::TrySpawnEnemyShip()//try? we do!
{
  MapManager.GetCurrentMap().AddObject(new CEnemyShip());
}
