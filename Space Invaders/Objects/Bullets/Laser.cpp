#include "Laser.h"

CLaser::CLaser(const IBaseObject * Owner, CVector2i StartPosition, EMoveDirection Direction) :
  IBaseObject(FAST_UPDATE, true),
  m_Owner(Owner)
{
  std::vector<std::string> Texture;
  Texture.push_back("-");
  SetTexture(Texture);
  SetPosition(StartPosition);

  m_MoveVector = GetMoveVector(Direction);
}

const IBaseObject * CLaser::GetOwner() const
{
  return m_Owner;
}

void CLaser::Update(double time)
{
  SetPosition(GetBounds().pos + m_MoveVector);
}
