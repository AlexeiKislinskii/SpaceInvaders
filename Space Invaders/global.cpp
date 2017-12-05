#include "Game.h"
#include "InputHandler.h"
#include <Windows.h>
#include <chrono>


/*
FIRST PRIORITE!!Need to fix self killing on forward moving
Add pause logic for all updateable objects, call it on game pause, also in this logic remove first fire on game starting
Delete UserInput.h
*/

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

  freq.QuadPart /= 2;//hack!, because i know that my cpu has 2 cores

  EGameState result = PAUSED_BY_USER;
  while (result != EXIT)
  {
    QueryPerformanceCounter(&time);
    CInputHandler::GetInstance().Update();
    result = CGame::GetInstance().Update((double)(time.QuadPart) / (double)(freq.QuadPart));
  }
}