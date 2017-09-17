#include "Rock.h"

CRock::CRock(CVector2i StartPosition, bool Upend) :
  IBaseObject(NON_UPDATE, false),
  m_IsUpended(Upend)
{
  SetPosition(StartPosition);
  SetMortality(false);
}

void CRock::Generate()
{
  size_t Height = 4 + rand() % 6;
  size_t Width = Height * 2;

  std::vector<std::string> Texture(Height);

  for (std::string & Row : Texture)
    for (size_t i = 0; i < Width; i++)
      Row += ' ';

  for (size_t i = 0; i < Height; i++)
  {
    size_t PosWithOffset = Height - 1 - i;
    Texture[m_IsUpended ? PosWithOffset : i][PosWithOffset] = m_IsUpended ? '\\' : '/';
    Texture[m_IsUpended ? PosWithOffset : i][Height + i] = m_IsUpended ? '/' : '\\';
  }
  for (size_t i = 0; i < Height; i++)
  {
    size_t PosWithOffset = Height - 1 - i;
    size_t XPos = m_IsUpended ? PosWithOffset : i;
    for (size_t j = 0; j < Width; j++)
    {
      if (j < PosWithOffset || j > Height + i)
        Texture[XPos][j] = ' ';
      else if (j > PosWithOffset && j < Height + i)
        Texture[XPos][j] = '@';
    }
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

  ////need to srand
  //size_t Height = 4 + rand() % 10;
  //size_t Width = 4 + rand() % 10;


}

void CRock::Update(double time)
{
}
