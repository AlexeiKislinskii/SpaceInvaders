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

  m_Weapon = new CLaserLauncher(MOVE_RIGHT);

#ifdef _DEBUG
  SetMortality(false);
#endif // _DEBUG
}

void CPlayerShip::Update(double time)
{
  IBaseShip::Update(time);
  Renderer.SetRenderPosition(GetBounds().pos.y - m_YAxisOffsetByUser);

  if (m_IsFireFromUser)
    m_Weapon->TryFire(time, GetBounds().pos + CVector2i(1, 5));

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

void CPlayerShip::ChangeFireState(bool state)
{
  m_IsFireFromUser = state;
}
