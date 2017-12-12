#include "Game.h"
#include "InputHandler.h"
#include <Windows.h>
#include <chrono>

void main()
{
  time_t CurrentRawTime = time(0);
  struct tm CurrentTime;
  localtime_s(&CurrentTime, &CurrentRawTime);
  std::string output = "";
  output = "Game start " + std::to_string(CurrentTime.tm_year + 1900);
  output += "/"          + std::to_string(CurrentTime.tm_mon + 1);
  output += "/"          + std::to_string(CurrentTime.tm_mday + 1);
  output += " "          + std::to_string(CurrentTime.tm_hour);
  output += ":"          + std::to_string(CurrentTime.tm_min);
  LOG(output);
#ifdef NDEBUG
  srand((unsigned int)time((time_t)0));
#endif // NDEBUG

  CGame::CreateInstance();
  CInputHandler::CreateInstance();

  CGame::GetInstance().Init();

  LARGE_INTEGER time, freq;

  ASSERT(QueryPerformanceFrequency(&freq), "CPU frequency unknown! Update will work wrong!");

  EGameState result = JUST_STARTED;
  while (result != EXIT)
  {
    ASSERT(QueryPerformanceCounter(&time), "Current time unknown! Update will work wrong!");
    CInputHandler::GetInstance().Update();
    result = CGame::GetInstance().Update((double)(time.QuadPart) / (double)(freq.QuadPart));
  }

  LOG("Game finished\n");
}