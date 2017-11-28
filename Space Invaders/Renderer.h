#pragma once
#include "Objects\BaseObject.h"
#include "Interfaces\Updateable.h"

class CRenderer : 
  public IUpdateable
{
public:
  CRenderer();

  void Add(IBaseObject & Object);

  const CRect GetScreenRect() const;

  void SetRenderPosition(int Position);// part of huge hack with Y render offset and ship cruise control

  void Clear();

protected:
  void Update(double time) override;

private:
  void Output();
  void UpdateHUD();

  void * m_ConsoleHandle;
  size_t m_ScreenHeight;
  size_t m_ScreenWidth;

  std::vector<std::string> m_LastRenderMap;
  std::vector<std::string> m_CurrentRenderMap;

  int m_CameraYPosition;
};

