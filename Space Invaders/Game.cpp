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
  if (m_MainMenu)
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

  //Order is important!
  m_MapManager->Init();
  m_Render->Init();
  m_ShipManager->Init();
  m_MainMenu->Init({ "New Game", "Continue", "Test", "Test" , "Test" }, 0);
  m_MainMenu->Enable(CSignal<int>::MakeDelegate(this, &CGame::MenuCallback));

  //CInputHandler::GetInstance().Signal.Connect(this, &CGame::InputHandler);
}

EGameState CGame::Update(double time)
{
  if (m_GameState == PLAYING)
  {
    m_Render->TryUpdate(time);
    m_MapManager->Update(time);
    m_CollisionEngine->TryUpdate(time);
  }
  else if(m_GameState == PAUSED_BY_USER)
  {
    m_MainMenu->Update();
  }

  return m_GameState;
}

void CGame::InputHandler(EInput input, bool isPressed)
{
  if (!isPressed)
    return;

  if (input == INPUT_ESC)
  {
    m_GameState = PAUSED_BY_USER;
    m_Render->Clear();
    m_MainMenu->Enable(CSignal<int>::MakeDelegate(this, &CGame::MenuCallback));
  }
}

void CGame::MenuCallback(int index)
{
  if (index == 0)
    m_GameState = PLAYING;
  else if (index == -1)
    m_GameState = EXIT;

  m_MainMenu->Disable();
  m_Render->Clear();
}
