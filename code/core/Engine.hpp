#ifndef BEFOXY_CORE_ENGINE_HPP
#define BEFOXY_CORE_ENGINE_HPP

#include <vector>
#include <chrono>

#include "core/Component.hpp"

class Engine
{
public:
    using TimePoint = std::chrono::system_clock::time_point;
    using Clock = std::chrono::system_clock;
public:
  Engine();
public:
  void init(const Workday& workday);
public:
  Sprint sprint() const;
  void tap();
  void skip();
  void update();
  const Workday& workday() const;

private:  
  Workday m_ideal;
  Workday m_current;
  TimePoint m_sprintEnd;
};

#endif // BEFOXY_CORE_ENGINE_HPP
