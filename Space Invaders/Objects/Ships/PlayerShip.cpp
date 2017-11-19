#include "PlayerShip.h"
#include "../../Weapons/LaserLauncher.h"
#include "../../Game.h"

CPlayerShip::CPlayerShip() :
  IBaseShip(MOVE_RIGHT),
  m_YAxisOffsetByUser(0),
  m_MoveFromUser(),
  m_IsFireFromUser(false)
{
  std::vector<std::string> Texture;
  Texture.push_back("/-   ");
  Texture.push_back("|@>>>");
  Texture.push_back("\\-   ");
  SetTexture(Texture);
  SetPosition(CVector2i(10, Renderer.GetScreenRect().pos.y));
  //mabe we should do like in enemy ship, place random and several times, and be immortal some time?
  
  m_Weapon = new CLaserLauncher(this, CVector2i(1, 5), MOVE_RIGHT);

  CInputHandler::GetInstance().Signal.Connect(this, &CPlayerShip::InputHandler);

#ifdef _DEBUG
  SetMortality(false);
#endif // _DEBUG
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

void CPlayerShip::AddMove(const CVector2i & move)
{
  if (m_MoveFromUser.x != move.x)
    m_MoveFromUser.x += move.x;

  if (m_MoveFromUser.y != move.y)
    m_MoveFromUser.y += move.y;
}

void CPlayerShip::InputHandler(EInput input, bool isPressed)
{
  switch (input)
  {
  case INPUT_A:
  case INPUT_LEFT:
    AddMove(CVector2i(0, isPressed ? -1 : 1));
    break;
  case INPUT_D:
  case INPUT_RIGHT:
    AddMove(CVector2i(0, isPressed ? 1 : -1));
    break;
  case INPUT_W:
  case INPUT_UP:
    AddMove(CVector2i(isPressed ? -1 : 1, 0));
    break;
  case INPUT_S:
  case INPUT_DOWN:
    AddMove(CVector2i(isPressed ? 1 : -1, 0));
    break;
  case INPUT_SPACE:
    m_IsFireFromUser = isPressed;
    break;
  default:
    break;
  }
}
