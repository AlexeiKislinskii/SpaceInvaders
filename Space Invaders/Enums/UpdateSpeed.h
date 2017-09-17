#pragma once
#include "../GameConsts.h"
#include <float.h>

enum EUpdateSpeed
{
  SLOW_UPDATE,
  NORMAL_UPDATE,
  FAST_UPDATE,
  NON_UPDATE
};

static double GetUpdateIntervale(EUpdateSpeed type)
{
  switch (type)
  {
  case SLOW_UPDATE:
    return MINIMAL_OBJECT_UPDATE_INTERVALE * 12.0;
  case NORMAL_UPDATE:
    return MINIMAL_OBJECT_UPDATE_INTERVALE * 6.0;
  case FAST_UPDATE:
    return MINIMAL_OBJECT_UPDATE_INTERVALE;
  case NON_UPDATE:
  default:
    return DBL_MAX;
  }
}
