#pragma once
#include "..\Objects\BaseObject.h"

struct CCollisionMapElement
{
  CCollisionMapElement();

  bool Occupy(IBaseObject * Member);

  bool IsOccupied() const;
  const IBaseObject * GetMember() const;

private:
  bool m_IsOccupied;
  IBaseObject * m_Member;
};
