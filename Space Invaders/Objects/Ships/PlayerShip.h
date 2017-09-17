#pragma once
#include "BaseShip.h"
#include "../../InputHandler.h"

class CPlayerShip : 
  public IBaseShip
{
public:
  CPlayerShip();

  int GetPositionForCamera() const;

  void AddMove(const CVector2i & move);
  void ChangeFireState(bool state);

protected:
  void Update(double time) override;

private:
  int m_YAxisOffsetByUser;

  CVector2i m_MoveFromUser;
  bool      m_IsFireFromUser;
};

