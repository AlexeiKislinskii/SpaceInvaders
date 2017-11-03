#pragma once
#include "BaseShip.h"
#include "../../InputHandler.h"

class CPlayerShip : 
  public IBaseShip
{
public:
  CPlayerShip();

  int GetPositionForCamera() const;

protected:
  void Update(double time) override;

private:
  void AddMove(const CVector2i & move);
  void InputHandler(EInput input, bool isPressed);

  int m_YAxisOffsetByUser;

  CVector2i m_MoveFromUser;
  bool      m_IsFireFromUser;
};

