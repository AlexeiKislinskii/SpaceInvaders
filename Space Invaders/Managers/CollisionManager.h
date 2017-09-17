#pragma once
#include "../Interfaces/Updateable.h"
#include "../Objects/BaseObject.h"

//All methods can be static, but do we need this?
class CCollisionEngine :
  public IUpdateable
{
public:
  CCollisionEngine();

  bool CanBePlaced(IBaseObject * object);

protected:
  void Update(double time) override;
};

