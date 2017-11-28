#pragma once
#include <string>

#define ASSERT CAssert::Assert
#define LOG CAssert::Log

class CAssert
{
public:

  static void Assert( bool isPassed, std::string errorLog = "");
  static void Log( std::string log );
};

