#pragma once

template<class T>
class ISingletone
{
public:
  static void CreateInstance()
  {
    if (!p_instance)
      p_instance = new T();
  }

  static T & GetInstance() 
  {
    return *p_instance;
  }

private:
  static T * p_instance;
};

