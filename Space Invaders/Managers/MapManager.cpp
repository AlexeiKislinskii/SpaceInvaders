#include "MapManager.h"

CMapManager::CMapManager() :
  m_CurrentMap(nullptr)
{
}

CMapManager::~CMapManager()
{
  delete m_CurrentMap;
}

void CMapManager::Init()
{
  m_CurrentMap = new CBaseMap();//only for test! we should create real map, base map is a prototype
  ASSERT(m_CurrentMap, "Map creating failed!");

  m_CurrentMap->Generate();
}

void CMapManager::Reset()
{
  if(m_CurrentMap) delete m_CurrentMap;
  Init();
}

void CMapManager::Update(double time)
{
  m_CurrentMap->Update(time);
}
