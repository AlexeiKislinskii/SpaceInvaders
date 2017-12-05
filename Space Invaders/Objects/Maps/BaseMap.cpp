#include "BaseMap.h"
#include "../Rock.h"

CBaseMap::~CBaseMap()
{
  for (IBaseObject * obj : m_AllObjects)
    delete obj;
}

void CBaseMap::Generate()
{
  m_Width = 2000;
  int Height = 30;
  int PlacementPosition = 1;
  int Density = 40;

  while ((size_t)PlacementPosition < m_Width)
  {
    auto TopRock = new CRock(CVector2i(0, PlacementPosition), true);
    TopRock->Generate();
    AddObject(TopRock);
    auto BottomRock = new CRock(CVector2i(Height, PlacementPosition), false);
    BottomRock->Generate();
    AddObject(BottomRock);
    PlacementPosition += Density;
  }
}

void CBaseMap::AddObject(IBaseObject * object)
{
  m_AllObjects.push_front(object);
}

const std::list<IBaseObject*> & CBaseMap::GetAllObjects() const
{
  return m_AllObjects;
}

void CBaseMap::Update(double time)
{
  for (auto it = m_AllObjects.begin(); it != m_AllObjects.end();)
  {
    if ((*it)->IsDead())
    {
      delete *it;
      it = m_AllObjects.erase(it);
      continue;
    }
    (*it)->TryUpdate(time);
    ++it;
  }
}
