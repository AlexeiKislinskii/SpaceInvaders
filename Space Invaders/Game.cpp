#include "Game.h"
#include "InputHandler.h"

CGame * ISingletone<CGame>::p_instance = nullptr;

CGame::CGame() :
  m_MapManager(nullptr),
  m_ShipManager(nullptr),
  m_Render(nullptr),
  m_CollisionEngine(nullptr),
  m_PlayerProfile(nullptr),
  m_GameState(EXIT),
  m_MainMenu(nullptr)
{
}

CGame::~CGame()
{
  delete m_MapManager;
  delete m_ShipManager;
  delete m_Render;
  delete m_CollisionEngine;
  delete m_PlayerProfile;
  delete m_MainMenu;
}

void CGame::Init()
{
  m_MapManager = new CMapManager();
  ASSERT(m_MapManager, "Map manager fail!");
  m_ShipManager = new CShipManager();
  ASSERT(m_ShipManager, "Ship manager fail!");
  m_Render = new CRenderer();
  ASSERT(m_Render, "Render fail!");
  m_CollisionEngine = new CCollisionEngine();
  ASSERT(m_CollisionEngine, "Collision manager fail!");
  m_PlayerProfile = new CPlayerProfiler();
  ASSERT(m_PlayerProfile, "Player profile fail!");
  m_MainMenu = new CGameMenu();
  ASSERT(m_MainMenu, "Main menu fail!");

  CInputHandler::GetInstance().FocusSignal.Connect(this, &CGame::ConsoleFocusHandler);

  PauseGame(JUST_STARTED);
}

EGameState CGame::Update(double time)
{
  if (m_GameState == PLAYING)
  {
    m_CollisionEngine->TryUpdate(time);
    m_ShipManager->TryUpdate(time);
    m_MapManager->Update(time);
    m_Render->TryUpdate(time);

    if (m_PlayerProfile->IsLifeEnded())
      PauseGame(PAUSED_FAIL);
  }
  else if(m_GameState != EXIT)
  {
    m_MainMenu->Update();
  }

  return m_GameState;
}

void CGame::ConsoleFocusHandler(bool isFocused)
{
  if (!isFocused && m_GameState == PLAYING)
    PauseGame(PAUSED_BY_USER);
}

void CGame::PauseGame(EGameState state)
{
  if(m_GameState == state)
    return;

  m_Render->Clear();
  m_GameState = state;

  int startMenuIndex = 0;
  MenuList list;
  list.push_back({"New Game", std::bind(&CGame::StartNewGame, this)});
  if (state == PAUSED_BY_USER)
  {
    list.push_back({"Continue", std::bind(&CGame::ContinueGame, this)});
    startMenuIndex = 1;
  }
  else if (state == JUST_STARTED || state == PAUSED_FAIL)
    list.push_back({"Load Game", std::bind(&CGame::LoadGame, this)});
  list.push_back({"Exit", std::bind(&CGame::ExitGame, this)});
  m_MainMenu->Show(list, startMenuIndex);
}

void CGame::StartNewGame()
{
  m_Render->SetRenderPosition(0);
  m_MapManager->Reset();
  m_ShipManager->Init();
  m_PlayerProfile->Reset();
  ContinueGame();
}

void CGame::LoadGame()
{
}

void CGame::ContinueGame()
{
  if (m_GameState == PLAYING)
    return;

  m_GameState = PLAYING;
  m_MainMenu->Hide();
  m_Render->Clear();
}

void CGame::ExitGame()
{
  m_GameState = EXIT;
}
