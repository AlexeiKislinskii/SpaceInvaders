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

  const std::vector<EInput> & GetUserInput() const;

  CSignal<const std::vector<EInput> &> Signal;
  CSignal<bool>         FocusSignal;
private:
  const HANDLE m_Handle;
  std::vector<EInput> m_UserInputList;
};

