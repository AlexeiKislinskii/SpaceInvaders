#pragma once
#include "BaseObject.h"

class CRock : 
  public IBaseObject
{
public:
  CRock(CVector2i StartPosition, bool Upend);

  void Generate();

protected:
  void Update(double time);

private:
  bool m_IsUpended;
};
