#pragma once
#include "../BaseObject.h"
#include "../../Enums/MoveDirection.h"

class CLaser : 
  public IBaseObject
{
public:
  CLaser(CVector2i StartPosition, EMoveDirection Direction);

protected:
  void Update(double time) override;

private:
  IBaseObject * m_Laser;
  CVector2i m_MoveVector;
};

