#include "InputHandler.h"
#include "Game.h"

CInputHandler * ISingletone<CInputHandler>::p_instance = nullptr;

CInputHandler::CInputHandler() :
  m_Handle(GetStdHandle(STD_INPUT_HANDLE))
{
  //move from constructor to init
  DWORD mode;

  //prevent selecting with mouse
  GetConsoleMode(m_Handle, &mode);
  mode &= ~ENABLE_QUICK_EDIT_MODE;
  SetConsoleMode(m_Handle, mode);

  //prevent from resizing
  HWND hwnd = GetConsoleWindow();
  LONG dwStyle = GetWindowLong(hwnd, GWL_STYLE);
  dwStyle ^= WS_THICKFRAME;//disable resize by mouse near edges
  dwStyle ^= WS_MAXIMIZEBOX;//disable maximize button n right top corner
  SetWindowLong(hwnd, GWL_STYLE, dwStyle);
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
        switch (m_Event[i].Event.KeyEvent.wVirtualKeyCode)
        {
        case 65://A
          Signal.Emit(INPUT_A, isPressed);
          break;
        case 37://left arrow
          Signal.Emit(INPUT_LEFT, isPressed);
          break;
        case 68://D
          Signal.Emit(INPUT_D, isPressed);
          break;
        case 39://right arrow
          Signal.Emit(INPUT_RIGHT, isPressed);
          break;
        case 87://W
          Signal.Emit(INPUT_W, isPressed);
          break;
        case 38://up arrow
          Signal.Emit(INPUT_UP, isPressed);
          break;
        case 83://S
          Signal.Emit(INPUT_S, isPressed);
          break;
        case 40://down arrow
          Signal.Emit(INPUT_DOWN, isPressed);
          break;
        case 32://space
          Signal.Emit(INPUT_SPACE, isPressed);
          break;
        case 27://escape
          Signal.Emit(INPUT_ESC, isPressed);
          break;
        }
      }
      /*else if(m_Event[i].EventType == FOCUS_EVENT)
      {
        if(m_Event[i].Event.FocusEvent.bSetFocus != false)
          OutputDebugString(L"Focused\n");
        else
          OutputDebugString(L"UnFocused\n");
      }*/
    }
  }
}
