#include "CollisionMapElement.h"

CCollisionMapElement::CCollisionMapElement() :
  m_IsOccupied(false),
  m_Member(nullptr)
{
}

bool CCollisionMapElement::Occupy(const IBaseObject * Member)
{
  if (m_IsOccupied)
    return false;

  m_IsOccupied = true;
  m_Member = Member;

  return true;
}

bool CCollisionMapElement::IsOccupied() const 
{ 
  return m_IsOccupied; 
}

const IBaseObject * CCollisionMapElement::GetMember() const 
{ 
  return m_Member; 
}