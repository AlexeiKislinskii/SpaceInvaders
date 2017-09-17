#pragma once
#include "../Structs/Vector.h"

enum EMoveDirection
{
  MOVE_LEFT,
  MOVE_RIGHT
};

static CVector2i GetMoveVector(EMoveDirection direction)
{
  switch (direction)
  {
  case MOVE_LEFT:
    return CVector2i(0, -1);
  default:
  case MOVE_RIGHT:
    return CVector2i(0, 1);
  }
}