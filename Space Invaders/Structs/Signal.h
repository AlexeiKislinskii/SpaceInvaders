#pragma once
#include <functional>
#include <vector>

template <typename... Args>
class CSignal
{
public:
  // connects a member function to this Signal
  template <typename T>
  void connect_member(T *inst, void (T::*func)(Args...))
  {
    m_slots.push_back([=](Args... args) { (inst->*func)(args...); });
  }

  // calls all connected functions
  void emit(Args... p)
  {
    for (auto it : m_slots) it(p...);
  }

private:
  std::vector<std::function<void(Args...)>> m_slots;
};