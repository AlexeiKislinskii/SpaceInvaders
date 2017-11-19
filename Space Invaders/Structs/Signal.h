#pragma once
#include <functional>
#include <map>
#include <vector>

//rework to https://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class

template <typename... Args>
class CSignal
{
public:
  CSignal() : current_id(0), isEmitted(false) {}

  // connects a member function to this Signal return index for further deleting
  template <typename T>
  int Connect(T *inst, void (T::*func)(Args...))
  {
    m_slots.insert(std::make_pair(++current_id, [=](Args... args) { (inst->*func)(args...); }));
    return current_id;
  }

  void Disconnect(const int index)
  {
    m_IdForErase.push_back(index);
    if (isEmitted)
      return;

    DisconnectInternal();
  }

  // calls all connected functions
  void Emit(Args... p)
  {
    isEmitted = true;
    for (auto it : m_slots) it.second(p...);
    isEmitted = false;

    DisconnectInternal();
  }

private:
  void DisconnectInternal()
  {
    for (auto i : m_IdForErase) m_slots.erase(i);
    m_IdForErase.clear();
  }

  int current_id;
  std::map<int, std::function<void(Args...)>> m_slots;

  bool isEmitted;
  std::vector<int> m_IdForErase;
};