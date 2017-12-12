#include "Vector.h"

CVector2i::CVector2i() :
  x(0),
  y(0)
{
}

CVector2i::CVector2i(int X, int Y) :
  x(X),
  y(Y)
{
}

CVector2i::CVector2i(const CVector2i & Value) :
  x(Value.x),
  y(Value.y)
{
}

void CVector2i::operator=(const CVector2i & Value)
{
  x = Value.x;
  y = Value.y;
}

void CVector2i::operator+=(const CVector2i & Value)
{
  x += Value.x;
  y += Value.y;
}

const CVector2i CVector2i::operator+(const CVector2i & Value) const
{
  return CVector2i(x + Value.x, y + Value.y);
}

const CVector2i CVector2i::operator-(const CVector2i & Value) const
{
  return CVector2i(x - Value.x, y - Value.y);
}

bool CVector2i::operator==(const CVector2i & Value) const
{
  return x == Value.x && y == Value.y;
}

bool CVector2i::operator!=(const CVector2i & Value) const
{
  return x != Value.x || y != Value.y;
}