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
    ReadConsoleInput(m_Handle, m_Event, 3, &count);
    for (size_t i = 0; i < count; i++)
    {
      if (m_Event[i].EventType == KEY_EVENT)
      {
        switch (m_Event[i].Event.KeyEvent.wVirtualKeyCode)
        {
        case 65://A
        case 37://left arrow
          ShipManager.GetPlayerShip().AddMove(
            CVector2i(0, m_Event[i].Event.KeyEvent.bKeyDown ? -1 : 1));
          break;
        case 68://D
        case 39://right arrow
          ShipManager.GetPlayerShip().AddMove(
            CVector2i(0, m_Event[i].Event.KeyEvent.bKeyDown ? 1 : -1));
          break;
        case 87://W
        case 38://up arrow
          ShipManager.GetPlayerShip().AddMove(
            CVector2i(m_Event[i].Event.KeyEvent.bKeyDown ? -1 : 1, 0));
          break;
        case 83://S
        case 40://down arrow
          ShipManager.GetPlayerShip().AddMove(
            CVector2i(m_Event[i].Event.KeyEvent.bKeyDown ? 1 : -1, 0));
          break;
        case 32://space
          ShipManager.GetPlayerShip().ChangeFireState(
            m_Event[i].Event.KeyEvent.bKeyDown ? true : false);
          break;
        case 27://escape
          if(!m_Event[i].Event.KeyEvent.bKeyDown)
            CGame::GetInstance().SetPause();
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