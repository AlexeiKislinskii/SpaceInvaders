#include "Assert.h"
#include <intrin.h>
#include <Windows.h>

void CAssert::Assert(bool isPassed, std::string errorLog)
{
  if ( !isPassed )
  {
    LOG( errorLog.empty() ? "No description" : errorLog );
    __debugbreak();
  }
}

void CAssert::Log(std::string log)
{
  OutputDebugString(std::wstring(log.begin(), log.end()).data());
}