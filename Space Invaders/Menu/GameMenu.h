#pragma once
#include <vector>
#include <string>

#include "../InputHandler.h"

class CGameMenu
{
public:
  CGameMenu();

  void Init(std::vector<std::string> items, int startIndex);

  void Enable(std::function<void(int)> callback);
  void Disable();


  void Update();
private:
  void InputHandle(EInput input, bool isPressed);

  const HANDLE             m_Handle;
  std::vector<std::string> m_Items;
  int                      m_Index;
  int                   m_IndexInInputHandler;
  std::function<void(int)> m_ChooseCallback;
};

