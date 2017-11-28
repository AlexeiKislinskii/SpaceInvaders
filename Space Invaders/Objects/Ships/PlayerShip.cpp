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

  std::string t = "User move vector x:";
  t += std::to_string( m_MoveFromUser.x );
  t += " y:";
  t += std::to_string( m_MoveFromUser.y);
  t += "\n";
  LOG(t);
}

int CPlayerShip::GetPositionForCamera() const
{
  return GetBounds().pos.y - m_YAxisOffsetByUser;
}

void CPlayerShip::InputHandler(EInput input, bool isPressed)
{
  switch (input)
  {
  case INPUT_A:
  case INPUT_LEFT:
  {
    int move = isPressed ? -1 : 1;
    if ( m_MoveFromUser.y != move )
      m_MoveFromUser.y += move;
    break;
  }
  case INPUT_D:
  case INPUT_RIGHT:
  {
    int move = isPressed ? 1 : -1;
    if ( m_MoveFromUser.y != move )
      m_MoveFromUser.y += move;
    break;
  }
  case INPUT_W:
  case INPUT_UP:
  {
    int move = isPressed ? -1 : 1;
    if ( m_MoveFromUser.x != move )
      m_MoveFromUser.x += move;
    break;
  }
  case INPUT_S:
  case INPUT_DOWN:
  {
    int move = isPressed ? 1 : -1;
    if ( m_MoveFromUser.x != move )
      m_MoveFromUser.x += move;
    break;
  }
  case INPUT_SPACE:
    m_IsFireFromUser = isPressed;
    break;
  default:
    break;
  }
}
