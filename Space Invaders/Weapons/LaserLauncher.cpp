#include "LaserLauncher.h"
#include "../Game.h"

CLaserLauncher::CLaserLauncher(EMoveDirection Direction) :
  IBaseWeapon(0.0),
  m_Direction(Direction)
{
}

void CLaserLauncher::Fire(CVector2i Position)
{
  MapManager.GetCurrentMap().AddObject(new CLaser(Position, m_Direction));
}
