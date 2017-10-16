#include "LaserLauncher.h"
#include "../Game.h"
#include "../Objects/Bullets/Laser.h"

CLaserLauncher::CLaserLauncher(IBaseShip * owner, CVector2i bulletOffset, EMoveDirection Direction) :
  IBaseWeapon(bulletOffset, Direction, 0.0),
  m_Owner(owner)
{
  // Empty
}

void CLaserLauncher::Fire()
{
  MapManager.GetCurrentMap().AddObject(new CLaser(m_Owner, m_Owner->GetBounds().pos + m_BulletOffset, m_Direction));
}
