#pragma once
#include "BaseShip.h"
#include "../../InputHandler.h"

class CPlayerShip : 
  public IBaseShip
{
public:
  CPlayerShip();
  ~CPlayerShip();

  int GetPositionForCamera() const;

protected:
  void Update(double time) override;

private:
  void InputHandler(EInput input, bool isPressed);

  int m_ConnectIndex;
  int m_YAxisOffsetByUser;

  CVector2i m_MoveFromUser;
  bool      m_IsFireFromUser;
};

