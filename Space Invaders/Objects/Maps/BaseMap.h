#pragma once
#include "../BaseObject.h"
#include <list>

//This class should be moved from objects folder

class CBaseMap
{
public:
  ~CBaseMap();

  void Generate();

  void Update(double time);

  void AddObject(IBaseObject * object);

  const std::list<IBaseObject *> & GetAllObjects() const;

  const size_t & GetWidth() const { return m_Width; };

private:
  size_t m_Width;
  size_t m_Height;

  std::list<IBaseObject *> m_AllObjects;
};