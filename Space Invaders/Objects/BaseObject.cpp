﻿#include "BaseObject.h"
#include "../Game.h"

IBaseObject::IBaseObject(const IBaseObject * Owner, EUpdateSpeed UpdateSpeed, bool IsMoveable) :
  IUpdateable(UpdateSpeed),
  m_Bounds(),
  m_Texture(),
  m_Edges(),
  m_IsMortal(true),
  m_IsOnScreen(true),//hack!should be default false and then logic in setPosition
  m_IsMoveable(IsMoveable),
  m_IsDead(false),
  m_Killer(nullptr),
  m_Owner(Owner)
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

const CRect & IBaseObject::GetBounds() const
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

void IBaseObject::SetTexture(std::vector<std::string> & Texture)
{
  m_Texture = std::move(Texture);
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
      ASSERT(CurrentWidth == m_Texture[i - 1].size(), "Not all rows in texture same size!");

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

bool IBaseObject::IsDead() const
{
  return m_IsDead;
}

void IBaseObject::TryKill(const IBaseObject * killer) const
{
  if (m_IsMortal)
  {
    if (killer && (this == killer->m_Owner || this->m_Owner == killer))
      return;

    m_IsDead = true;
    m_Killer = killer;
  }
}

const IBaseObject * IBaseObject::GetKiller() const
{
  return m_Killer;
}

const IBaseObject * const IBaseObject::GetOwner() const
{
  return m_Owner;
}
