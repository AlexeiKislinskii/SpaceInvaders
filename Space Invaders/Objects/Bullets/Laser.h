#pragma once
#include "../BaseObject.h"
#include "../../Enums/MoveDirection.h"

class CLaser : 
  public IBaseObject
{
public:
  CLaser(const IBaseObject * Owner, CVector2i StartPosition, EMoveDirection Direction);

protected:
  void Update(double time) override;

private:
  CVector2i m_MoveVector;
};

