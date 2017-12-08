#include "Laser.h"

CLaser::CLaser(const IBaseObject * Owner, CVector2i StartPosition, EMoveDirection Direction) :
  IBaseObject(Owner, FAST_UPDATE, true)
{
  std::vector<std::string> Texture;
  Texture.push_back("-");
  SetTexture(Texture);
  SetPosition(StartPosition);

  m_MoveVector = GetMoveVector(Direction);
}

void CLaser::Update(double time)
{
  SetPosition(GetBounds().pos + m_MoveVector);
}
