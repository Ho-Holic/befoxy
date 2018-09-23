#ifndef BEFOXY_CORE_ENGINE_HPP
#define BEFOXY_CORE_ENGINE_HPP

#include <vector>

#include "core/Component.hpp"

class Engine
{
public:
  Engine();
public:
  void init(const Workday& workday);
public:
  Sprint sprint() const;
  void tap();
  void skip();  
  const Workday& workday() const;

private:  
  Workday m_ideal;
  Workday m_current;
  TimePoint m_sprintEnd;
};

#endif // BEFOXY_CORE_ENGINE_HPP
