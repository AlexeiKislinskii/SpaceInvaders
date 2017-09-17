#include "Game.h"

CGame * ISingletone<CGame>::p_instance = nullptr;

CGame::CGame() :
  m_MapManager(nullptr),
  m_ShipManager(nullptr),
  m_Render(nullptr),
  m_CollisionEngine(nullptr),
  m_PlayerProfile(nullptr),
  m_IsUserRequestPause(false)
{
}

CGame::~CGame()
{
  if (m_MapManager)
    delete m_MapManager;
  if (m_ShipManager)
    delete m_ShipManager;
  if (m_Render)
    delete m_Render;
  if (m_CollisionEngine)
    delete m_CollisionEngine;
  if (m_PlayerProfile)
    delete m_PlayerProfile;
}

void CGame::Init()
{
  m_MapManager = new CMapManager();
  m_ShipManager = new CShipManager();
  m_Render = new CRenderer();
  m_CollisionEngine = new CCollisionEngine();
  m_PlayerProfile = new CPlayerProfiler();

  //Order is important!
  m_MapManager->Init();
  m_Render->Init();
  m_ShipManager->Init();
}

EGameState CGame::Update(double time)
{
  m_Render->TryUpdate(time);
  m_MapManager->Update(time);
  m_CollisionEngine->TryUpdate(time);

  return m_IsUserRequestPause ? STOPED_BY_USER : PLAYING;
}

void CGame::SetPause()
{
  m_IsUserRequestPause = true;
}
