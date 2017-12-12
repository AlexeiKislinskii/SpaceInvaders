#include "InputHandler.h"
#include "Game.h"

CInputHandler * ISingletone<CInputHandler>::p_instance = nullptr;

CInputHandler::CInputHandler() :
  m_Handle(GetStdHandle(STD_INPUT_HANDLE))
{
  DWORD mode;

  //prevent selecting with mouse
  ASSERT(GetConsoleMode(m_Handle, &mode), "GetConsoleMode failed!");
  mode &= ~ENABLE_QUICK_EDIT_MODE;
  ASSERT(SetConsoleMode(m_Handle, mode), "SetConsoleMode failed!");

  //prevent from resizing
  HWND hwnd = GetConsoleWindow();
  LONG dwStyle = GetWindowLong(hwnd, GWL_STYLE);
  dwStyle ^= WS_THICKFRAME;//disable resize by mouse near edges
  dwStyle ^= WS_MAXIMIZEBOX;//disable maximize button in right top corner
  ASSERT(SetWindowLong(hwnd, GWL_STYLE, dwStyle), "SetWindowLong failed!");
}

void CInputHandler::Update()
{
  if (WaitForSingleObject(m_Handle, 0) == WAIT_OBJECT_0)
  {
    DWORD count = 0;
    INPUT_RECORD m_Event[3];
    if (!ReadConsoleInput(m_Handle, m_Event, 3, &count))
      return;

    for (size_t i = 0; i < count; i++)
    {
      if (m_Event[i].EventType == KEY_EVENT)
      {
        bool isPressed = m_Event[i].Event.KeyEvent.bKeyDown == 0 ? false : true;
        EInput userInput;
        switch (m_Event[i].Event.KeyEvent.wVirtualKeyCode)
        {
        case 65: userInput = INPUT_A;     break; //A
        case 37: userInput = INPUT_LEFT;  break; //left arrow
        case 68: userInput = INPUT_D;     break; //D
        case 39: userInput = INPUT_RIGHT; break; //right arrow
        case 87: userInput = INPUT_W;     break; //W
        case 38: userInput = INPUT_UP;    break; //up arrow
        case 83: userInput = INPUT_S;     break; //S
        case 40: userInput = INPUT_DOWN;  break; //down arrow
        case 32: userInput = INPUT_SPACE; break; //space
        case 27://escape
          FocusSignal.Emit(false);
          return;
        default:
          return;
        }

        if(!m_UserInputList.empty() && m_UserInputList.back() == userInput && isPressed)
          return;

        if (isPressed)
          m_UserInputList.push_back(userInput);
        else
          for (auto it = m_UserInputList.begin(); it != m_UserInputList.end();)
            ((*it) == userInput) ? (it = m_UserInputList.erase(it)) : it++;

        Signal.Emit(m_UserInputList);
      }
      else if(m_Event[i].EventType == FOCUS_EVENT)
      {
        for (auto it = m_UserInputList.begin(); it != m_UserInputList.end();)
        {
          SHORT result = 0;
          switch (*it)
          {
          case INPUT_A:     result = GetKeyState(65); break; //A
          case INPUT_LEFT:  result = GetKeyState(37); break; //left arrow
          case INPUT_D:     result = GetKeyState(68); break; //D
          case INPUT_RIGHT: result = GetKeyState(39); break; //right arrow
          case INPUT_W:     result = GetKeyState(87); break; //W
          case INPUT_UP:    result = GetKeyState(38); break; //up arrow
          case INPUT_S:     result = GetKeyState(83); break; //S
          case INPUT_DOWN:  result = GetKeyState(40); break; //down arrow
          case INPUT_SPACE: result = GetKeyState(32); break; //space
          }

          if (result & 0x8000)
          {
            it++;
            continue;
          }

          it = m_UserInputList.erase(it);
        }
        FocusSignal.Emit(m_Event[i].Event.FocusEvent.bSetFocus != false);
      }
    }
  }
}

const std::vector<EInput>& CInputHandler::GetUserInput() const
{
  return m_UserInputList;
}
