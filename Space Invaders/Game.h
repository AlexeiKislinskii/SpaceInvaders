#pragma once
#include "Enums\GameState.h"
#include "InputHandler.h"
#include "Interfaces\Singletone.h"
#include "Managers\MapManager.h"
#include "Managers\ShipManager.h"
#include "Managers\CollisionManager.h"
#include "Renderer.h"
#include "PlayerProfiler.h"

#define MapManager CGame::GetInstance().GetMapManager()
#define ShipManager CGame::GetInstance().GetShipManager()
#define Renderer CGame::GetInstance().GetRenderer()
#define PlayerProfile CGame::GetInstance().GetPlayerProfile()
#define CollisionManager CGame::GetInstance().GetCollisionManager()

class CGame : 
  public ISingletone<CGame>
{
public:
  CGame();
  ~CGame();

  void Init();

  EGameState Update(double time);

  CMapManager & GetMapManager() const { return *m_MapManager; };
  CShipManager & GetShipManager() const { return *m_ShipManager; };
  CRenderer & GetRenderer() const { return *m_Render; };
  CPlayerProfiler & GetPlayerProfile() const { return *m_PlayerProfile; };
  CCollisionEngine & GetCollisionManager() const { return *m_CollisionEngine; };

  void SetPause();

private:
  CMapManager * m_MapManager;
  CShipManager * m_ShipManager;
  CRenderer * m_Render;
  CCollisionEngine * m_CollisionEngine;
  CPlayerProfiler * m_PlayerProfile;

  bool m_IsUserRequestPause;
};

