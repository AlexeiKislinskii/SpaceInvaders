#include <iostream>
#include <Windows.h>

#include "GameMenu.h"
#include "../Game.h"

#define WHITEONBLACKTEXT BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN
#define BLACKONWHITETEXT FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN

CGameMenu::CGameMenu() :
  m_Handle(GetStdHandle(STD_OUTPUT_HANDLE)),
  m_InputSignalIndex(-1),
  m_Index(-1)
{
  // Empty
}

void CGameMenu::Show(MenuList & items, int startIndex)
{
  m_Items = std::move(items);
  m_Index = startIndex;
  m_InputSignalIndex = CInputHandler::GetInstance().Signal.Connect(this, &CGameMenu::InputHandle);
}

void CGameMenu::Hide()
{
  m_Items.clear();
  CInputHandler::GetInstance().Signal.Disconnect(m_InputSignalIndex);
}

void CGameMenu::InputHandle(EInput input, bool isPressed)
{
  if (!isPressed && !m_Items.empty())
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
      m_Items[m_Index].second();
      break;
    }
  }
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
    SHORT startPos = (SHORT)(HorizontalMiddle - (m_Items[i].first.size() / 2));
    SetConsoleCursorPosition(m_Handle, COORD{ startPos, (SHORT)(VerticalStartPos + i) });
    std::cout << m_Items[i].first;
  }
}
