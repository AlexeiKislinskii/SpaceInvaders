#pragma once
#include <vector>
#include <string>

#include "../InputHandler.h"
#include "../Enums/GameState.h"

typedef std::vector<std::pair<std::string, std::function<void(void)>>> MenuList;

class CGameMenu
{
public:
  CGameMenu();

  void Show(MenuList & items, int startIndex);
  void Hide();

  void Update();
private:
  void InputHandle(EInput input, bool isPressed);

  const HANDLE m_Handle;
  int          m_InputSignalIndex;
  MenuList     m_Items;
  size_t       m_Index;
};

