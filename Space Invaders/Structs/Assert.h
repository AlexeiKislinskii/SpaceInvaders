#pragma once
#include <string>

#define ASSERT CAssert::Assert
#define LOG CAssert::Log

class CAssert
{
public:

  static void Assert(void * isPassed, const std::string & errorLog = "");
  static void Assert(int isPassed, const std::string & errorLog = "");
  static void Assert(bool isPassed, const std::string & errorLog = "");
  static void Log(const std::string & log);
};

