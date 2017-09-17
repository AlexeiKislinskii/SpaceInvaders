#pragma once
#include "Interfaces\Singletone.h"
#include "Structs\Vector.h"
#include <Windows.h>

class CInputHandler :
  public ISingletone<CInputHandler>
{
public:
  CInputHandler();

  void Update();

private:
  const HANDLE m_Handle;
};

