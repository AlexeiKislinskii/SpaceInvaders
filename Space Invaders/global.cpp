#include "Game.h"
#include "InputHandler.h"
#include <Windows.h>
#include <chrono>

void main()
{
#ifdef NDEBUG
  srand((unsigned int)time((time_t)0));
#endif // NDEBUG

  CGame::CreateInstance();
  CInputHandler::CreateInstance();

  CGame::GetInstance().Init();

  LARGE_INTEGER time, freq;

  QueryPerformanceFrequency(&freq);

  EGameState result = JUST_STARTED;
  while (result != EXIT)
  {
    QueryPerformanceCounter(&time);
    CInputHandler::GetInstance().Update();
    result = CGame::GetInstance().Update((double)(time.QuadPart) / (double)(freq.QuadPart));
  }
}