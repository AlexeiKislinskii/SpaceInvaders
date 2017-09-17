#include "Rectangular.h"

CRect::CRect() : 
  pos(), 
  height(0), 
  width(0) 
{
}

CRect::CRect(CVector2i Pos, size_t Height, size_t Width) :
  pos(Pos),
  height(Height),
  width(Width) 
{
}