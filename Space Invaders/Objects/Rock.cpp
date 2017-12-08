#include "Rock.h"

CRock::CRock(CVector2i StartPosition, bool Upend) :
  IBaseObject(nullptr, NON_UPDATE, false),
  m_IsUpended(Upend)
{
  SetPosition(StartPosition);
  SetMortality(false);
}

void CRock::Generate()
{
  size_t Height = 4 + rand() % 6;

  std::vector<std::string> Texture(Height);

  for (std::string & Row : Texture)
    Row.resize(Height * 2, ' ');

  for (size_t i = 0; i < Height; i++)
  {
    size_t PosWithOffset = Height - i - 1;
    size_t XPos = m_IsUpended ? PosWithOffset : i;

    for (size_t j = PosWithOffset + 1; j < Height + i; j++)
      Texture[XPos][j] = '@';

    Texture[XPos][PosWithOffset] = m_IsUpended ? '\\' : '/';
    Texture[XPos][Height + i] = m_IsUpended ? '/' : '\\';
  }

  SetTexture(Texture);

  if (!m_IsUpended)
  {
    auto Bounds = GetBounds();
    Bounds.pos.x -= (int)Bounds.height;
    SetPosition(Bounds.pos);
  }
}

void CRock::Update(double time)
{
  // Empty
}
