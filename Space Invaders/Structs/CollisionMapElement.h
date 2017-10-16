#pragma once
#include "..\Objects\BaseObject.h"

struct CCollisionMapElement
{
  CCollisionMapElement();

  bool Occupy(const IBaseObject * Member);

  bool IsOccupied() const;
  const IBaseObject * GetMember() const;

private:
  bool m_IsOccupied;
  const IBaseObject * m_Member;
};
