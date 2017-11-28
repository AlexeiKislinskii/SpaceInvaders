#include "Game.h"
#include "InputHandler.h"

CGame * ISingletone<CGame>::p_instance = nullptr;

CGame::CGame() :
  m_MapManager(nullptr),
  m_ShipManager(nullptr),
  m_Render(nullptr),
  m_CollisionEngine(nullptr),
  m_PlayerProfile(nullptr),
  m_GameState(PAUSED_BY_USER),
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
  m_ShipManager = new CShipManager();
  m_Render = new CRenderer();
  m_CollisionEngine = new CCollisionEngine();
  m_PlayerProfile = new CPlayerProfiler();
  m_MainMenu = new CGameMenu();

  CInputHandler::GetInstance().Signal.Connect(this, &CGame::InputHandler);

  MenuList list;
  list.push_back({ "New Game",  std::bind(&CGame::StartNewGame, this) });
  list.push_back({ "Load Game", std::bind(&CGame::LoadGame,     this) });
  list.push_back({ "Exit",      std::bind(&CGame::ExitGame,     this) });
  m_MainMenu->Show(list, 0);
}

EGameState CGame::Update(double time)
{
  if (m_GameState == PLAYING)
  {    
    m_CollisionEngine->TryUpdate(time);
    m_ShipManager->TryUpdate(time);
    m_MapManager->Update(time);
    m_Render->TryUpdate(time);
  }
  else if(m_GameState == PAUSED_BY_USER)
  {
    m_MainMenu->Update();
  }

  return m_GameState;
}

void CGame::InputHandler(EInput input, bool isPressed)
{
  if (input == INPUT_ESC && !isPressed)
  {
    m_Render->Clear();
    m_GameState = PAUSED_BY_USER;

    MenuList list;
    list.push_back({ "New Game", std::bind(&CGame::StartNewGame, this) });
    list.push_back({ "Continue", std::bind(&CGame::ContinueGame, this) });
    list.push_back({ "Exit",     std::bind(&CGame::ExitGame,     this) });
    m_MainMenu->Show(list, 1);
  }
}
void CGame::StartNewGame()
{
  m_GameState = PLAYING;
  m_MainMenu->Hide();
  m_Render->Clear();
  m_MapManager->Reset();
  m_ShipManager->Init();
}

void CGame::LoadGame()
{
}

void CGame::ContinueGame()
{
  m_GameState = PLAYING;
  m_MainMenu->Hide();
  m_Render->Clear();
}

void CGame::ExitGame()
{
  m_GameState = EXIT;
}
