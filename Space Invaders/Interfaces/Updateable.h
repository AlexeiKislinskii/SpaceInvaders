#pragma once
#include "../Enums/UpdateSpeed.h"

class IUpdateable
{
public:
  IUpdateable(EUpdateSpeed updateSpeed);

  virtual void TryUpdate  (double time) final;
  virtual void PauseUpdate(double time) final;

protected:
  virtual void Update(double time) = 0;

private:
  double m_NextUpdateTime;
  double m_UpdateInterval;

  bool   m_IsPaused;
  double m_PauseTime;
};
