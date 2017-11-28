#include "CollisionMap.h"

CollisionMap::CollisionMap(size_t start, size_t height, size_t width) :
  m_StartAt(start),
  m_Height(height),
  m_Width(width)
{
  m_Map = new CCollisionMapElement*[m_Height];
  for (size_t i = 0; i < m_Height; i++)
    m_Map[i] = new CCollisionMapElement[m_Width];
}

CollisionMap::~CollisionMap()
{
  for (size_t i = 0; i < m_Height; ++i)
    delete[] m_Map[i];
  delete[] m_Map;
}

const IBaseObject * CollisionMap::AddMember(const IBaseObject * NewMember)
{
  const IBaseObject * Output = nullptr;
  auto Pos = NewMember->GetBounds().pos;
  auto Texture = NewMember->GetTexture();

  for (size_t i = 0; i < Texture.size(); i++)
  {
    for (size_t j = 0; j < Texture[i].size(); j++)
    {
      if (Texture[i][j] == ' ')
        continue;

      auto PointLocalCord = WorldToLocalPosition(CVector2i(Pos.x + i, Pos.y + j));

      if (PointLocalCord.x < 0 || PointLocalCord.x >= (int)m_Height || 
          PointLocalCord.y < 0 || PointLocalCord.y >= (int)m_Width)
        continue;

      if (!m_Map[PointLocalCord.x][PointLocalCord.y].Occupy(NewMember))
        Output = m_Map[PointLocalCord.x][PointLocalCord.y].GetMember();
    }
  }

  return Output;
}

void CollisionMap::CleanFrom(const IBaseObject * Member)
{
  auto Pos = Member->GetBounds().pos;
  auto Texture = Member->GetTexture();

  for (size_t i = 0; i < Texture.size(); i++)
  {
    for (size_t j = 0; j < Texture[i].size(); j++)
    {
      if (Texture[i][j] == ' ')
        continue;

      auto PointLocalCord = WorldToLocalPosition(CVector2i(Pos.x + i, Pos.y + j));

      if (PointLocalCord.x < 0 || PointLocalCord.x >= (int)m_Height ||
          PointLocalCord.y < 0 || PointLocalCord.y >= (int)m_Width)
        continue;

      m_Map[PointLocalCord.x][PointLocalCord.y] = CCollisionMapElement();
    }
  }
}

CVector2i CollisionMap::WorldToLocalPosition(CVector2i WorldPos)
{
  return CVector2i(WorldPos.x, WorldPos.y - (int)m_StartAt);
}
