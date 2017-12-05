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
        EInput userInput;
        switch (m_Event[i].Event.KeyEvent.wVirtualKeyCode)
        {
        case 65://A
          userInput = INPUT_A;
          break;
        case 37://left arrow
          userInput = INPUT_LEFT;
          break;
        case 68://D
          userInput = INPUT_D;
          break;
        case 39://right arrow
          userInput = INPUT_RIGHT;
          break;
        case 87://W
          userInput = INPUT_W;
          break;
        case 38://up arrow
          userInput = INPUT_UP;
          break;
        case 83://S
          userInput = INPUT_S;
          break;
        case 40://down arrow
          userInput = INPUT_DOWN;
          break;
        case 32://space
          userInput = INPUT_SPACE;
          break;
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
        FocusSignal.Emit( m_Event[i].Event.FocusEvent.bSetFocus != false );
      }
    }
  }
}

const std::vector<EInput>& CInputHandler::GetUserInput() const
{
  return m_UserInputList;
}
