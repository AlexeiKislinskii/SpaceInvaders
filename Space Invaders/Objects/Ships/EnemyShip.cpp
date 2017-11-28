#include "EnemyShip.h"
#include "../../Game.h"
#include "../../Weapons/LaserLauncher.h"

CEnemyShip::CEnemyShip() :
  IBaseShip(MOVE_RIGHT)
{
  std::vector<std::string> Texture;
  Texture.push_back("   /");
  Texture.push_back("<<(@");
  Texture.push_back("   \\");
  SetTexture(Texture);
  auto Rect = Renderer.GetScreenRect();

  int failCounter = 0;
  do
  {
    SetPosition(CVector2i((rand() % 10) + (((int)Rect.height / 2) - 5 - 3), Rect.pos.y + (int)Rect.width));//Hack! 20 and 10 should be calculated from possible rock height
  } while (!CollisionManager.CanBePlaced(this) && failCounter++ > 10);

  ASSERT(failCounter < 10, "Cannot generate enemy ship!");

  m_Weapon = new CLaserLauncher(this, CVector2i(1, -1), MOVE_LEFT);

  m_State = SPAWNING;
  SetMortality(false);
  m_MoveVector = CVector2i(0, -1);
}

CEnemyShip::~CEnemyShip()
{
}

void CEnemyShip::Update(double time)
{
  IBaseShip::Update(time);

  switch (m_State)
  {
  case SPAWNING:
  {
    TryMove(m_MoveVector, true);

    auto Bounds = GetBounds();
    auto Rect = Renderer.GetScreenRect();
    if (Bounds.pos.y + (int)Bounds.width + 5 < Rect.pos.y + (int)Rect.width)
    {
      m_State = FLYING;
      SetMortality(true);
      m_FireIntervaleInUpdates = 0;
      RandomizeMoveVector();
    }
    break;
  }
  case FLYING:
  {
    TryMove(m_MoveVector);
    if (m_FireIntervaleInUpdates++ == 5)
      m_State = FIRING;
    break; 
  }
  case FIRING:
    m_Weapon->TryFire(time);
    m_FireIntervaleInUpdates = 0;
    RandomizeMoveVector();
    m_State = FLYING;
    break;
  }
}

void CEnemyShip::RandomizeMoveVector()
{
  m_MoveVector.x = rand() % 3 - 1;
  m_MoveVector.y = rand() % 3 - 1;
}
