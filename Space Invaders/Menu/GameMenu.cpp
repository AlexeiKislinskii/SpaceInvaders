#include <iostream>
#include <Windows.h>

#include "GameMenu.h"
#include "../Game.h"

#define WHITEONBLACKTEXT BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN
#define BLACKONWHITETEXT FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN

CGameMenu::CGameMenu() : 
  m_Handle(GetStdHandle(STD_OUTPUT_HANDLE)),
  m_IndexInInputHandler(-1)
{
  // Empty
}

void CGameMenu::Init(std::vector<std::string> items, int startIndex)
{
  m_Items = items;
  m_Index = startIndex;
}

void CGameMenu::InputHandle(EInput input, bool isPressed)
{
  if (!isPressed)
  {
    switch (input)
    {
    case INPUT_W:
    case INPUT_UP:
      m_Index = m_Index > 0 ? m_Index - 1 : (int)m_Items.size() - 1;
      break;
    case INPUT_S:
    case INPUT_DOWN:
      m_Index = m_Index < m_Items.size() - 1 ? m_Index + 1 : 0;
      break;
    case INPUT_SPACE:
      m_ChooseCallback(m_Index);
      break;
    case INPUT_ESC:
      m_ChooseCallback(-1);
      break;
    }
  }
}

void CGameMenu::Enable(std::function<void(int)> callback)
{
  m_ChooseCallback = callback;
  m_IndexInInputHandler = CInputHandler::GetInstance().Signal.Connect(this, &CGameMenu::InputHandle);
}

void CGameMenu::Disable()
{
  m_ChooseCallback = nullptr;
  CInputHandler::GetInstance().Signal.Disconnect(m_IndexInInputHandler);
}

void CGameMenu::Update()
{
  CONSOLE_SCREEN_BUFFER_INFO CursorBufferInfo;

  GetConsoleScreenBufferInfo(m_Handle, &CursorBufferInfo);
  auto HorizontalMiddle = (CursorBufferInfo.srWindow.Right - CursorBufferInfo.srWindow.Left + 1) / 2;
  auto VerticalStartPos = ((CursorBufferInfo.srWindow.Bottom - CursorBufferInfo.srWindow.Top + 1) / 2) - (m_Items.size() / 2);

  for (int i = 0; i < m_Items.size(); i++)
  {
    SetConsoleTextAttribute(m_Handle, i == m_Index ? WHITEONBLACKTEXT : BLACKONWHITETEXT);
    SHORT startPos = (SHORT)(HorizontalMiddle - (m_Items[i].size() / 2));
    SetConsoleCursorPosition(m_Handle, COORD{ startPos, (SHORT)(VerticalStartPos + i) });
    std::cout << m_Items[i];
  }
}
