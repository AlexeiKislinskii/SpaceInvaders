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
  const CVector2i operator+(const CVector2i & Value) const;
  const CVector2i operator-(const CVector2i & Value) const;
  void operator+=(const CVector2i & Value);

  //Logical overload
  bool operator==(const CVector2i & Value) const;
  bool operator!=(const CVector2i & Value) const;
};