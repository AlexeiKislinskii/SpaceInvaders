#pragma once
#include <vector>
#include <list>
#include "../Structs/Rectangular.h"
#include "../Structs/Vector.h"
#include "../../Interfaces/Updateable.h"

class IBaseObject : 
  public IUpdateable
{
public:
  IBaseObject(EUpdateSpeed UpdateSpeed, bool IsMoveable);
  virtual ~IBaseObject();

  const std::vector<std::string> & GetTexture() const;
  
  const std::vector<CVector2i> & GetEdges() const;
  CRect GetBounds() const;
  bool IsMortal() const;
  bool IsMoveable() const;

  void SetIsOnScreen(bool state);
  bool IsOnScreen() const;

  virtual void Kill(const IBaseObject * killer) const;

protected:
  void SetTexture(std::vector<std::string> Texture);
  void SetPosition(CVector2i Position);
  void SetMortality(bool value);

private:
  void CalculateEdges();

  std::vector<std::string> m_Texture;
  std::vector<CVector2i> m_Edges;
  CRect m_Bounds;

  bool m_IsMoveable;
  bool m_IsMortal;
  bool m_IsOnScreen;
};
