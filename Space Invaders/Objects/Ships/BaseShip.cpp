#include "BaseShip.h"
#include "../../Game.h"

IBaseShip::IBaseShip(EMoveDirection direction) :
  IBaseObject(NORMAL_UPDATE, true),
  m_Weapon(nullptr),
  m_IsCruiseControleEnebled(true)
{
  m_CruiseControleVector = GetMoveVector(direction);
}

IBaseShip::~IBaseShip()
{
  if(m_Weapon) delete m_Weapon;
}

void IBaseShip::Update(double time)
{
  if (m_IsCruiseControleEnebled)
    SetPosition(GetBounds().pos + m_CruiseControleVector);
}

void IBaseShip::DisableCruiseControl()
{
  m_IsCruiseControleEnebled = false;
}

bool IBaseShip::TryMove(const CVector2i & moveVector, bool force)
{
  if (moveVector.x == 0 && moveVector.y == 0)
    return false;

  auto ScreenRect = Renderer.GetScreenRect();
  auto ShipBounds = GetBounds();

  ShipBounds.pos += moveVector;

  if (!force && 
      (ShipBounds.pos.x < 0 ||
      ShipBounds.pos.x + ShipBounds.height > (int)ScreenRect.height ||
      ShipBounds.pos.y < (int)ScreenRect.pos.y ||
      ShipBounds.pos.y - ScreenRect.pos.y + ShipBounds.width > (int)ScreenRect.width))
    return false;

  SetPosition(ShipBounds.pos);

  return true;
}
