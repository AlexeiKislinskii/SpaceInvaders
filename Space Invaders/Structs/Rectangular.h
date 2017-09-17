#pragma once
#include "Vector.h"

struct CRect
{
  CVector2i pos;

  size_t height;
  size_t width;

  CRect();
  CRect(CVector2i Pos, size_t Height, size_t Width);
};

