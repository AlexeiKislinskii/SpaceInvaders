#pragma once
#include "Interfaces\Singletone.h"
#include "Structs\Vector.h"
#include "Structs/Signal.h"
#include "Enums/Input.h"
#include <Windows.h>

class CInputHandler :
  public ISingletone<CInputHandler>
{
public:
  CInputHandler();

  void Update();

  CSignal<EInput, bool> Signal;
private:
  const HANDLE m_Handle;
};

