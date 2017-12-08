#include "CollisionManager.h"
#include "../Game.h"
#include "../Structs/CollisionMap.h"

CCollisionEngine::CCollisionEngine() :
  IUpdateable(FAST_UPDATE)
{
}

void CCollisionEngine::Update(double time)
{
  auto rect = Renderer.GetScreenRect();
  auto & CurrentMap = MapManager.GetCurrentMap();
  auto & Objects = CurrentMap.GetAllObjects();

  CollisionMap Map(rect.pos.y, rect.height, rect.width);

  for (auto obj : Objects)
  {
    if (!obj->IsOnScreen())
    {
      obj->TryKill(nullptr);
      continue;
    }

    auto object = Map.AddMember(obj);
    if (object)
    {
      obj->TryKill(object);
      object->TryKill(obj);
    }
  }
}

bool CCollisionEngine::CanBePlaced(IBaseObject * object)//awful name
{
  CRect Bounds = object->GetBounds();
  auto & Objects = MapManager.GetCurrentMap().GetAllObjects();

  CollisionMap Map(Bounds.pos.y, Renderer.GetScreenRect().height, Bounds.width);

  if (Map.AddMember(object))
    return false;

  for (auto it = Objects.begin(); it != Objects.end(); it++)
    if (Map.AddMember(*it))
      return false;

  return true;
}