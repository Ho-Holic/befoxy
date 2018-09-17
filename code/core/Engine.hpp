#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>

#include "core/Component.hpp"

class Engine
{
public:
  Engine();
public:
  void init(const Workday& workday);
public:
  Sprint sprint();
  void tap();
  void skip();
  void update();
  const Workday& workday() const;

private:  
  Workday m_ideal;
  Workday m_current;
};

#endif // ENGINE_HPP
