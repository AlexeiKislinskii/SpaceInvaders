#pragma once
#include "CollisionMapElement.h"

struct CollisionMap
{
  CollisionMap(size_t start, size_t height, size_t width);

  ~CollisionMap();

  //Function take pointer to new member, add all his edges in total map
  //if collision happen return pointer to object with which a collision occurred and 
  //if collision not happen returned value is nullptr
  const IBaseObject * AddMember(const IBaseObject * NewMember);

  void CleanFrom(const IBaseObject * Member);

private:
  CVector2i WorldToLocalPosition(CVector2i WorldPos);

  size_t m_StartAt;
  size_t m_Height;
  size_t m_Width;
  CCollisionMapElement ** m_Map;
};
