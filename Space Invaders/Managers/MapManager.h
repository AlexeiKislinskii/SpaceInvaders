#pragma once
#include "..\Objects\Maps\BaseMap.h"

class CMapManager
{
public:
  CMapManager();
  ~CMapManager();

  void Init();
  void Reset();
  
  void Pause(double time);
  void Update(double time);

  CBaseMap & GetCurrentMap() const { return *m_CurrentMap; };

private:
  CBaseMap * m_CurrentMap;
};

