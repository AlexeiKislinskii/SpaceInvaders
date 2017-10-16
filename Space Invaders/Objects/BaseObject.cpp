#include "BaseObject.h"
#include "../Game.h"
#include <assert.h>

IBaseObject::IBaseObject(EUpdateSpeed UpdateSpeed, bool IsMoveable) :
  IUpdateable(UpdateSpeed),
  m_Bounds(),
  m_Texture(),
  m_Edges(),
  m_IsMortal(true),
  m_IsOnScreen(true),//hack!should be default false and then logic in setPosition
  m_IsMoveable(IsMoveable)
{
  // Empty
}

IBaseObject::~IBaseObject()
{
  // Empty
}

const std::vector<std::string> & IBaseObject::GetTexture() const
{
  return m_Texture;
}

CRect IBaseObject::GetBounds() const
{
  return m_Bounds;
}

const std::vector<CVector2i>& IBaseObject::GetEdges() const
{
  return m_Edges;
}

bool IBaseObject::IsMortal() const
{
  return m_IsMortal;
}

bool IBaseObject::IsMoveable() const
{
  return m_IsMoveable;
}

void IBaseObject::SetTexture(std::vector<std::string> Texture)
{
  m_Texture = Texture;
  CalculateEdges();
}

void IBaseObject::SetPosition(CVector2i Position)
{
  m_Bounds.pos = Position;
}

void IBaseObject::SetMortality(bool value)
{
  m_IsMortal = value;
}

void IBaseObject::CalculateEdges()
{
  size_t MaxTextureWidht = 0;
  for(size_t i = 0; i < m_Texture.size(); i++)
  {
    size_t CurrentWidth = m_Texture[i].size();

    if (i != 0 && CurrentWidth != m_Texture[i - 1].size())
      assert(CurrentWidth == m_Texture[i - 1].size());

    MaxTextureWidht = MaxTextureWidht > CurrentWidth ? MaxTextureWidht : CurrentWidth;

    for (size_t j = 0; j < CurrentWidth; j++)
    {
      if (m_Texture[i][j] == ' ')
        continue;

      if (i == 0 ||
          i == m_Texture.size() - 1 ||
          j == 0 ||
          j == CurrentWidth - 1 ||
          m_Texture[i + 1][j] == ' ' ||
          m_Texture[i - 1][j] == ' ' ||
          m_Texture[i][j + 1] == ' ' ||
          m_Texture[i][j - 1] == ' ' ||
          m_Texture[i - 1][j - 1] == ' ' ||
          m_Texture[i + 1][j - 1] == ' ' ||
          m_Texture[i - 1][j + 1] == ' ' ||
          m_Texture[i + 1][j + 1] == ' ')
        m_Edges.push_back(CVector2i((int)i, (int)j));
    }
  }

  m_Bounds.height = m_Texture.size();
  m_Bounds.width = MaxTextureWidht;
}

void IBaseObject::SetIsOnScreen(bool state)
{
  m_IsOnScreen = state;
}

bool IBaseObject::IsOnScreen() const
{
  return m_IsOnScreen;
}

void IBaseObject::Kill(const IBaseObject * killer) const
{
  // Empty
}

