#pragma once
#include "Objects\BaseObject.h"
#include "Interfaces\Updateable.h"

static const int SCREEN_Y_OFFSET = -5;//temporary shit
class CRenderer : 
  public IUpdateable
{
public:
  CRenderer();

  void Init();
  void Add(IBaseObject & Object);

  const CRect GetScreenRect() const;

  void SetRenderPosition(int Position);

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

