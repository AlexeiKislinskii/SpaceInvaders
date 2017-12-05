#include "PlayerShip.h"
#include "../../Weapons/LaserLauncher.h"
#include "../../Game.h"

CPlayerShip::CPlayerShip() :
  IBaseShip(MOVE_RIGHT),
  m_YAxisOffsetByUser(0),
  m_MoveFromUser(),
  m_IsFireFromUser(false),
  m_ConnectIndex(-1)
{
  std::vector<std::string> Texture;
  Texture.push_back("/-   ");
  Texture.push_back("|@>>>");
  Texture.push_back("\\-   ");
  SetTexture(Texture);
  SetPosition(CVector2i(10, Renderer.GetScreenRect().pos.y));
  //mabe we should do like in enemy ship, place random and several times, and be immortal some time?
  
  m_Weapon = new CLaserLauncher(this, CVector2i(1, 5), MOVE_RIGHT);

  m_ConnectIndex = CInputHandler::GetInstance().Signal.Connect(this, &CPlayerShip::InputHandler);
  InputHandler(CInputHandler::GetInstance().GetUserInput());

#ifdef _DEBUG
  SetMortality(false);
#endif // _DEBUG
}

CPlayerShip::~CPlayerShip()
{
  CInputHandler::GetInstance().Signal.Disconnect(m_ConnectIndex);
}

void CPlayerShip::Update(double time)
{
  IBaseShip::Update(time);
  Renderer.SetRenderPosition(GetBounds().pos.y - m_YAxisOffsetByUser);

  if (m_IsFireFromUser)
    m_Weapon->TryFire(time);

  if (TryMove(m_MoveFromUser))
  {
    m_YAxisOffsetByUser += m_MoveFromUser.y;
    Renderer.SetRenderPosition(GetBounds().pos.y - m_YAxisOffsetByUser);
  }
}

int CPlayerShip::GetPositionForCamera() const
{
  return GetBounds().pos.y - m_YAxisOffsetByUser;
}

void CPlayerShip::InputHandler(const std::vector<EInput> & input)
{
  m_IsFireFromUser = false;
  m_MoveFromUser.x = 0;
  m_MoveFromUser.y = 0;

  for (int i = (int)input.size() - 1; i >= 0; i--)
  {
    if (input[i] == INPUT_SPACE)
      m_IsFireFromUser = true;
    if (m_MoveFromUser.x == 0 && (input[i] == INPUT_W || input[i] == INPUT_UP))
      m_MoveFromUser.x = -1;
    if (m_MoveFromUser.x == 0 && (input[i] == INPUT_S || input[i] == INPUT_DOWN))
      m_MoveFromUser.x = 1;
    if (m_MoveFromUser.y == 0 && (input[i] == INPUT_A || input[i] == INPUT_LEFT))
      m_MoveFromUser.y = -1;
    if (m_MoveFromUser.y == 0 && (input[i] == INPUT_D || input[i] == INPUT_RIGHT))
      m_MoveFromUser.y = 1;
  }
}
