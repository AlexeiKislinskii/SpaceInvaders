#pragma once
#include "../BaseObject.h"
#include "../../Enums/MoveDirection.h"

class CLaser : 
  public IBaseObject
{
public:
  CLaser(const IBaseObject * Owner, CVector2i StartPosition, EMoveDirection Direction);

  const IBaseObject * GetOwner() const;
protected:
  void Update(double time) override;

private:
  const IBaseObject * m_Owner;
  CVector2i m_MoveVector;
};

