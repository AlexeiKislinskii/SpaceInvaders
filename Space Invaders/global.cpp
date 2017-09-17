#include "Game.h"
#include "InputHandler.h"
#include <Windows.h>
#include <chrono>

void main()
{
#ifdef NDEBUG
  srand(time((time_t)0));
#endif // NDEBUG

  CGame::CreateInstance();
  CInputHandler::CreateInstance();

  CGame::GetInstance().Init();

  LARGE_INTEGER time, freq;

  QueryPerformanceFrequency(&freq);

  freq.QuadPart /= 2;//hack!, because i know that my cpu has 2 cores
  auto t = CInputHandler::GetInstance();
  EGameState result = PLAYING;
  while (result == PLAYING)
  {
    QueryPerformanceCounter(&time);
    CInputHandler::GetInstance().Update();
    result = CGame::GetInstance().Update((double)(time.QuadPart) / (double)(freq.QuadPart));
  }
}