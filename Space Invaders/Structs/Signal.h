#pragma once
#include <functional>
#include <map>

template <typename... Args>
class CSignal
{
public:
  CSignal() : current_id(0) {}

  template <typename T>
  static std::function<void(Args...)> MakeDelegate(T *inst, void (T::*func)(Args...))
  {
    return [=](Args... args) { (inst->*func)(args...); };
  }

  // connects a member function to this Signal return index for further deleting
  template <typename T>
  int Connect(T *inst, void (T::*func)(Args...))
  {
    m_slots.insert(std::make_pair(++current_id, MakeDelegate(inst, func)));
    return current_id;
  }

  void Disconnect(const int index)
  {
    m_slots.erase(index);
  }

  // calls all connected functions
  void Emit(Args... p)
  {
    for (auto it : m_slots) it.second(p...);
  }

private:
  int current_id;
  std::map<int, std::function<void(Args...)>> m_slots;
};