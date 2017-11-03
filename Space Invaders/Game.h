#pragma once
#include "Enums\GameState.h"
#include "Interfaces\Singletone.h"
#include "Managers\MapManager.h"
#include "Managers\ShipManager.h"
#include "Managers\CollisionManager.h"
#include "Renderer.h"
#include "PlayerProfiler.h"
#include "Menu/GameMenu.h"
#include "Enums/Input.h"

#define Game CGame::GetInstance()
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

private:
  void InputHandler(EInput input, bool isPressed);
  void MenuCallback(int index);

  CGameMenu * m_MainMenu;

  CMapManager * m_MapManager;
  CShipManager * m_ShipManager;
  CRenderer * m_Render;
  CCollisionEngine * m_CollisionEngine;
  CPlayerProfiler * m_PlayerProfile;

  EGameState m_GameState;
};

