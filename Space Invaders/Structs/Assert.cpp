#include "Assert.h"
#include <intrin.h>
#include <Windows.h>

void CAssert::Assert(void * isPassed, const std::string & errorLog)
{
  Assert(isPassed == nullptr ? false : true, errorLog);
}

void CAssert::Assert(int isPassed, const std::string & errorLog)
{
  Assert(isPassed == 0 ? false : true, errorLog);
}

void CAssert::Assert(bool isPassed, const std::string & errorLog)
{
  if (!isPassed)
  {
    LOG(errorLog.empty() ? "No description" : errorLog);
    __debugbreak();
  }
}

void CAssert::Log(const std::string & log)
{
  OutputDebugString(std::wstring(log.begin(), log.end()).data());
}
