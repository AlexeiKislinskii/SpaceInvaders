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

const CVector2i CVector2i::operator+(const CVector2i & Value)
{
  return CVector2i(x + Value.x, y + Value.y);
}

const CVector2i CVector2i::operator-(const CVector2i & Value)
{
  return CVector2i(x - Value.x, y - Value.y);
}

const CVector2i CVector2i::operator/=(const int Value) const
{
  return CVector2i(x / Value, y / Value);
}

bool CVector2i::operator==(const CVector2i & Value)
{
  return x == Value.x && y == Value.y;
}

bool CVector2i::operator!=(const CVector2i & Value)
{
  return x != Value.x || y != Value.y;
}

double CVector2i::Distance(CVector2i First, CVector2i Second)
{
  return sqrt(pow(Second.x - First.x, 2) + pow(Second.y - First.y, 2));
}

double CVector2i::Distance(CVector2i First, double SecondX, double SecondY)
{
  return sqrt(pow(SecondX - First.x, 2) + pow(SecondY - First.y, 2));
}