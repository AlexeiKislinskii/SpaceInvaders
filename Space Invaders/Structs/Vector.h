#pragma once
#include <math.h>

struct CVector2i
{
  int x, y;

  CVector2i();
  CVector2i(int X, int Y);
  CVector2i(const CVector2i & Value);

  void operator=(const CVector2i & Value);

  //Arithmetic overload
  const CVector2i operator+(const CVector2i & Value);
  const CVector2i operator-(const CVector2i & Value);
  void operator+=(const CVector2i & Value);
  const CVector2i operator/=(const int Value) const;

  //Logical overload
  bool operator==(const CVector2i & Value);
  bool operator!=(const CVector2i & Value);

  static double Distance(CVector2i First, CVector2i Second);
  static double Distance(CVector2i First, double SecondX, double SecondY);
};