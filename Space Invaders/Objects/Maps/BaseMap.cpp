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

  while (PlacementPosition < m_Width)
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

std::list<IBaseObject *>::const_iterator CBaseMap::DeleteObject(const IBaseObject * object)
{
  auto it = std::find(m_AllObjects.begin(), m_AllObjects.end(), object);

  if (it != m_AllObjects.end())
  {
    delete *it;
    it = m_AllObjects.erase(it);
  }

  return it;
}

const std::list<IBaseObject*> & CBaseMap::GetAllObjects() const
{
  return m_AllObjects;
}

void CBaseMap::Update(double time)
{
  for (IBaseObject * obj : m_AllObjects)
    obj->TryUpdate(time);
}
